//
// EPITECH PROJECT, 2024
// move_up
// File description:
// move command
//

#![allow(dead_code)]

use crate::tcp::command_handle::{CommandError, CommandHandler, ResponseResult};
use crate::tcp::TcpClient;

use log::info;

pub async fn move_up(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    info!("Moving up...");

    let response = client.check_dead("Forward\n").await?;
    client.handle_response(response).await
}
