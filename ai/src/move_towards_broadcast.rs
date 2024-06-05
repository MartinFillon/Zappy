//
// EPITECH PROJECT, 2024
// move_to_tile.rs
// File description:
// utility function to move towards a broadcast made by another player.
// stops when finding a player on tile n°0
//

use log::info;

use crate::{
    commands::{
        look_around, move_up,
        turn::{self, DirectionTurn},
    },
    tcp::{self, command_handle::Direction, TcpClient},
};

const Y_DIRS: [i32; 8] = [1, 1, 0, -1, -1, -1, 0, 1];
const X_DIRS: [i32; 8] = [0, -1, -1, -1, 0, 1, 1, 1];

fn get_dir_coordinates(dir: &Direction) -> (i32, i32) {
    (X_DIRS[dir.to_usize() - 1], Y_DIRS[dir.to_usize() - 1])
}

async fn move_left(client: &mut TcpClient) -> bool {
    if !turn::turn(client, DirectionTurn::Left).await {
        return false;
    }
    if !move_up::move_up(client).await {
        return false;
    }
    if !turn::turn(client, DirectionTurn::Right).await {
        return false;
    }
    true
}

async fn move_right(client: &mut TcpClient) -> bool {
    if !turn::turn(client, DirectionTurn::Right).await {
        return false;
    }
    if !move_up::move_up(client).await {
        return false;
    }
    if !turn::turn(client, DirectionTurn::Left).await {
        return false;
    }
    true
}

async fn move_player(client: &mut TcpClient, x: i32) -> bool {
    loop {
        if (x < 0 && !move_left(client).await) || (x > 0 && !move_right(client).await) {
            return false;
        }
        if !move_up::move_up(client).await {
            return false;
        }
        match look_around::look_around(client).await {
            Ok(tcp::command_handle::ResponseResult::Tiles(tiles)) => {
                if let Some(tile) = tiles.first() {
                    if tile.iter().filter(|obj| obj.as_str() == "player").count() > 1 {
                        break;
                    }
                }
            }
            Ok(_) => {
                info!("Error: Wrong type of result returned.");
                return false;
            }
            Err(e) => {
                info!("Error: {}.", e);
                return false;
            }
        }
    }
    true
}

pub async fn move_towards_broadcast(client: &mut TcpClient, dir: Direction) -> bool {
    info!("Moving towards direction {}...", dir);
    if dir == Direction::Center {
        return true;
    }
    let (mut x, y) = get_dir_coordinates(&dir);
    if y < 0 {
        x = -x;
        if !turn::turn(client, DirectionTurn::Right).await
            || !turn::turn(client, DirectionTurn::Right).await
        {
            return false;
        }
    }
    move_player(client, x).await
}
