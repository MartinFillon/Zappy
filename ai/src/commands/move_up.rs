//
// EPITECH PROJECT, 2024
// move_up
// File description:
// move command
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

use log::info;

pub async fn move_up(client: &mut TcpClient) -> bool {
    info!("Moving up...");
    let response = match client.check_dead("Forward\n").await {
        Ok(res) => res,
        Err(_) => return false,
    };
    matches!(response.trim_end(), "ok")
}
