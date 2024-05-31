//
// EPITECH PROJECT, 2024
// turn
// File description:
// turn 90° right and 90° left commands
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

use std::fmt::Display;

use log::info;

#[derive(Debug, Clone, Copy)]
pub enum Direction {
    Left,
    Right,
}

impl Display for Direction {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", DIRECTIONS[(*self) as usize])
    }
}

const DIRECTIONS: [&str; 2] = ["Left", "Right"];

pub async fn turn(client: &mut TcpClient, dir: Direction) -> bool {
    info!("Turning {}...", dir);
    let response = match client
        .check_dead(&format!("{}\n", DIRECTIONS[dir as usize]))
        .await
    {
        Ok(res) => res,
        Err(_) => return false,
    };
    matches!(response.as_str(), "ok\n")
}
