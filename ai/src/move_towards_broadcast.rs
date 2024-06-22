//
// EPITECH PROJECT, 2024
// move_towards_broadcast.rs
// File description:
// utility function to move towards a broadcast made by another player.
// stops when finding a player on tile n°0
//

use crate::{
    commands::{
        move_up,
        turn::{self, DirectionTurn},
    },
    move_to_tile::{move_left, move_right},
    tcp::{
        command_handle::{
            CommandError, DirectionEject, DirectionHandler, DirectionMessage, ResponseResult,
        },
        TcpClient,
    },
};

#[allow(unused_imports)]
use log::{debug, error, info, warn};

const Y_MSG_DIRS: [i32; 9] = [0, 1, 1, 0, -1, -1, -1, 0, 1];
const X_MSG_DIRS: [i32; 9] = [0, 0, -1, -1, -1, 0, 1, 1, 1];

const Y_EJECT_DIRS: [i32; 4] = [1, 0, -1, 0];
const X_EJECT_DIRS: [i32; 4] = [0, 1, 0, -1];

fn get_msg_coordinates(dir: &DirectionMessage) -> (i32, i32) {
    (X_MSG_DIRS[dir.to_usize()], Y_MSG_DIRS[dir.to_usize()])
}

fn get_eject_coordinates(dir: &DirectionEject) -> (i32, i32) {
    (
        X_EJECT_DIRS[dir.to_usize() - 1],
        Y_EJECT_DIRS[dir.to_usize() - 1],
    )
}

pub async fn turn_towards_broadcast(
    client: &mut TcpClient,
    dir: DirectionMessage,
) -> Result<ResponseResult, CommandError> {
    debug!("Turning towards direction {}...", dir);
    if dir == DirectionMessage::Center {
        return Ok(ResponseResult::OK);
    }
    let (mut x, y) = get_msg_coordinates(&dir);
    if y < 0 {
        x = -x;
        turn::turn(client, DirectionTurn::Right).await?;
        turn::turn(client, DirectionTurn::Right).await?;
    }
    if x < 0 {
        turn::turn(client, DirectionTurn::Left).await?;
    }
    if x > 0 {
        turn::turn(client, DirectionTurn::Right).await?;
    }
    Ok(ResponseResult::OK)
}

pub async fn move_towards_broadcast(
    client: &mut TcpClient,
    dir: DirectionMessage,
) -> Result<ResponseResult, CommandError> {
    debug!("Moving towards direction {}...", dir);
    if dir == DirectionMessage::Center {
        return Ok(ResponseResult::OK);
    }
    let (mut x, y) = get_msg_coordinates(&dir);
    if y < 0 {
        x = -x;
        turn::turn(client, DirectionTurn::Right).await?;
        turn::turn(client, DirectionTurn::Right).await?;
    }
    if x < 0 {
        move_left(client).await?;
    }
    if x > 0 {
        move_right(client).await?;
    }
    move_up::move_up(client).await
}

async fn undo_eject(client: &mut TcpClient, x: i32) -> bool {
    if (x < 0 && move_left(client).await.is_err()) || (x > 0 && move_right(client).await.is_err()) {
        return false;
    }
    if let Ok(ResponseResult::OK) = move_up::move_up(client).await {
        return true;
    }
    false
}

pub async fn backtrack_eject(client: &mut TcpClient, dir: DirectionEject) -> bool {
    info!("Backtracking back from ejection {}...", dir);
    let (mut x, y) = get_eject_coordinates(&dir);
    if y < 0 {
        x = -x;
        if turn::turn(client, DirectionTurn::Right).await.is_err() // to handle eject/message
            || turn::turn(client, DirectionTurn::Right).await.is_err()
        {
            return false;
        }
    }
    undo_eject(client, x).await
}

#[cfg(test)]
mod tests_broadcast_move {
    use crate::{
        move_towards_broadcast::{get_eject_coordinates, get_msg_coordinates},
        tcp::command_handle::{DirectionEject, DirectionMessage},
    };

    #[test]
    fn test_get_msg_coordinates() {
        let coords = get_msg_coordinates(&DirectionMessage::North);
        assert_eq!(coords, (0, 1));

        let coords = get_msg_coordinates(&DirectionMessage::NorthWest);
        assert_eq!(coords, (-1, 1));

        let coords = get_msg_coordinates(&DirectionMessage::West);
        assert_eq!(coords, (-1, 0));

        let coords = get_msg_coordinates(&DirectionMessage::South);
        assert_eq!(coords, (0, -1));

        let coords = get_msg_coordinates(&DirectionMessage::SouthWest);
        assert_eq!(coords, (-1, -1));

        let coords = get_msg_coordinates(&DirectionMessage::Center);
        assert_eq!(coords, (0, 0));

        let coords = get_msg_coordinates(&DirectionMessage::SouthEast);
        assert_eq!(coords, (1, -1));

        let coords = get_msg_coordinates(&DirectionMessage::NorthEast);
        assert_eq!(coords, (1, 1));
    }

    #[test]
    fn test_get_eject_coordinates() {
        let coords = get_eject_coordinates(&DirectionEject::North);
        assert_eq!(coords, (0, 1));

        let coords = get_eject_coordinates(&DirectionEject::South);
        assert_eq!(coords, (0, -1));

        let coords = get_eject_coordinates(&DirectionEject::East);
        assert_eq!(coords, (1, 0));

        let coords = get_eject_coordinates(&DirectionEject::West);
        assert_eq!(coords, (-1, 0));
    }
}
