//
// EPITECH PROJECT, 2024
// move_up
// File description:
// move command
//

#![allow(dead_code)]

use crate::tcp::{
    command_handle::{CommandError, CommandHandler, ResponseResult},
    TcpClient,
};

use log::debug;

pub async fn move_up(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    debug!("Moving up...");

    let response = client.check_dead("Forward\n").await?;
    client.handle_response(response).await
}
