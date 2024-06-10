//
// EPITECH PROJECT, 2024
// turn
// File description:
// turn 90° right and 90° left commands
//

#![allow(dead_code)]

use crate::tcp::command_handle::{CommandError, CommandHandler, ResponseResult};
use crate::tcp::TcpClient;

use std::fmt;
use std::fmt::{Display, Formatter};

use log::info;

#[derive(Debug, Clone, Copy)]
pub enum DirectionTurn {
    Left,
    Right,
}

impl Display for DirectionTurn {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "{}", DIRECTIONS[(*self) as usize])
    }
}

const DIRECTIONS: [&str; 2] = ["Left", "Right"];

pub async fn turn(
    client: &mut TcpClient,
    dir: DirectionTurn,
) -> Result<ResponseResult, CommandError> {
    info!("Turning {}...", dir);

    let response = client
        .check_dead(&format!("{}\n", DIRECTIONS[dir as usize]))
        .await?;
    client.handle_response(response).await
}
