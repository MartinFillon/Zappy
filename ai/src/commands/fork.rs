//
// EPITECH PROJECT, 2024
// fork
// File description:
// fork command
//

#![allow(dead_code)]

use crate::tcp::{
    command_handle::{CommandError, CommandHandler, ResponseResult},
    TcpClient,
};

use log::debug;

pub async fn fork(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    debug!("Forking...");

    let response = client.check_dead("Fork\n").await?;
    client.handle_response(response).await
}
