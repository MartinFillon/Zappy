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

use log::{debug, info};

const Y_MSG_DIRS: [i32; 8] = [1, 1, 0, -1, -1, -1, 0, 1];
const X_MSG_DIRS: [i32; 8] = [0, -1, -1, -1, 0, 1, 1, 1];

const Y_EJECT_DIRS: [i32; 4] = [1, 0, -1, 0];
const X_EJECT_DIRS: [i32; 4] = [0, 1, 0, -1];

fn get_msg_coordinates(dir: &DirectionMessage) -> (i32, i32) {
    (
        X_MSG_DIRS[dir.to_usize() - 1],
        Y_MSG_DIRS[dir.to_usize() - 1],
    )
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
    turn_towards_broadcast(client, dir).await?;
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
