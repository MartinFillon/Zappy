//
// EPITECH PROJECT, 2024
// eject
// File description:
// eject command
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

pub async fn eject(client: &mut TcpClient) -> Result<bool, bool> {
    let response = client.check_dead("Eject\n").await?;
    match response.as_str() {
        "ok\n" => Ok(true),
        _ => Ok(false),
    }
}
