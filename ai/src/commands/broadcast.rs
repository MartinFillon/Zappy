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

#[allow(unused_imports)]
use log::{debug, error, info, warn};

pub async fn broadcast(client: &mut TcpClient, msg: &str) -> Result<ResponseResult, CommandError> {
    debug!("Broadcasting: ({})...", msg);

    let key = client.crypt();
    let encrypted_res = match key.encrypt(msg.as_bytes().to_vec()) {
        Some(data) => data,
        None => return Err(CommandError::InvalidKey),
    };

    let response = client
        .check_dead(&format!("Broadcast {}\n", encrypted_res))
        .await?;
    client.handle_response(response).await
}
