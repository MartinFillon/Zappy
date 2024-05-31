//
// EPITECH PROJECT, 2024
// unused_slots
// File description:
// connect_nbr command
//

#![allow(dead_code)]

use crate::tcp::command_handle::{CommandError, CommandHandler, ResponseResult};
use crate::tcp::TcpClient;

use log::info;

pub async fn unused_slots(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    info!("Checking unused slots...");
    let response = client.check_dead("Connect_nbr\n").await?;
    match response.parse::<usize>() {
        Ok(nb) => Ok(ResponseResult::Value(nb)),
        Err(_) => Err(CommandError::InvalidResponse),
    }
}
