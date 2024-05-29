//
// EPITECH PROJECT, 2024
// move_up
// File description:
// move command
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

pub async fn move_up(client: &mut TcpClient) -> bool {
    let response = match client.check_dead("Forward\n").await {
        Ok(res) => res,
        Err(_) => return false,
    };
    matches!(response.as_str(), "ok\n")
}
