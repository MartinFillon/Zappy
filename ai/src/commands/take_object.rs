//
// EPITECH PROJECT, 2024
// take_object
// File description:
// take object command
//

#![allow(dead_code)]

use crate::tcp::{
    command_handle::{CommandError, CommandHandler, ResponseResult},
    TcpClient,
};

use log::debug;

pub async fn take_object(
    client: &mut TcpClient,
    obj: &str,
) -> Result<ResponseResult, CommandError> {
    debug!("Taking object: ({})...", obj);
    let response = client.check_dead(&format!("Take {}\n", obj)).await?;
    client.handle_response(response).await
}
