//
// EPITECH PROJECT, 2024
// drop_object
// File description:
// set object command
//

#![allow(dead_code)]

use crate::tcp::{
    command_handle::{CommandError, CommandHandler, ResponseResult},
    TcpClient,
};

use log::info;

pub async fn drop_object(
    client: &mut TcpClient,
    obj: &str,
) -> Result<ResponseResult, CommandError> {
    info!("Dropping object: ({})...", obj);
    let response = client.check_dead(&format!("Set {}\n", obj)).await?;
    client.handle_response(response).await
}
