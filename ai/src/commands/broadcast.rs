//
// EPITECH PROJECT, 2024
// broadcast
// File description:
// broadcast command
//

#![allow(dead_code)]

use crate::tcp::{
    command_handle::{CommandError, CommandHandler, ResponseResult},
    TcpClient,
};

use log::debug;

pub async fn broadcast(client: &mut TcpClient, msg: &str) -> Result<ResponseResult, CommandError> {
    debug!("Broadcasting: ({})...", msg);
    let response = client.check_dead(&format!("Broadcast {}\n", msg)).await?;
    client.handle_response(response).await
}
