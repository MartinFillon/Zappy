//
// EPITECH PROJECT, 2024
// turn
// File description:
// turn 90° right and 90° left commands
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

pub enum Direction {
    Left,
    Right,
}

const DIRECTIONS: [&str; 2] = ["Left", "Right"];

pub async fn turn(client: &mut TcpClient, dir: Direction) -> bool {
    let response = match client
        .check_dead(&format!("{}\n", DIRECTIONS[dir as usize]))
        .await
    {
        Ok(res) => res,
        Err(_) => return false,
    };
    match response.as_str() {
        "ok\n" => true,
        _ => false,
    }
}
