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

    let key = client.crypt();
    let encrypted_res = match key.encrypt(response.as_bytes().to_vec()) {
        Some(data) => data,
        None => return Err(CommandError::InvalidKey),
    };
    client.handle_response(encrypted_res).await
}
