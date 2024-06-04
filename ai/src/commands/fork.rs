//
// EPITECH PROJECT, 2024
// fork
// File description:
// fork command
//

#![allow(dead_code)]

use crate::tcp::command_handle::{CommandError, CommandHandler, ResponseResult};
use crate::tcp::TcpClient;

use log::info;

pub async fn fork(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    info!("Forking...");
    let response = client.check_dead("Fork\n").await?;
    client.handle_response(response).await
}
