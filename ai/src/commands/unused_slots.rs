//
// EPITECH PROJECT, 2024
// unused_slots
// File description:
// connect_nbr command
//

#![allow(dead_code)]

use crate::tcp::{
    command_handle::{CommandError, CommandHandler, ResponseResult},
    TcpClient,
};

#[allow(unused_imports)]
use log::{debug, error, info, warn};

pub async fn unused_slots(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    debug!("Checking unused slots...");

    let response = client.check_dead("Connect_nbr\n").await?;
    client.handle_response(response).await
}
