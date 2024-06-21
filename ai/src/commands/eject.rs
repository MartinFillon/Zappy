//
// EPITECH PROJECT, 2024
// eject
// File description:
// eject command
//

#![allow(dead_code)]

use crate::tcp::{
    command_handle::{CommandError, CommandHandler, ResponseResult},
    TcpClient,
};

pub async fn eject(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    let response = client.check_dead("Eject\n").await?;
    client.handle_response(response).await
}
