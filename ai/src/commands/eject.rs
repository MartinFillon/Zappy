//
// EPITECH PROJECT, 2024
// eject
// File description:
// eject command
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

use log::info;

pub async fn eject(client: &mut TcpClient) -> Result<bool, bool> {
    info!("Ejecting...");
    let response = client.check_dead("Eject\n").await?;
    client.handle_response(response).await
}
