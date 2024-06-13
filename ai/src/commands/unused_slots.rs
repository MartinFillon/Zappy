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

use log::debug;

pub async fn unused_slots(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    debug!("Checking unused slots...");
    let response = client.check_dead("Connect_nbr\n").await?;
    match response.parse::<usize>() {
        Ok(nb) => Ok(ResponseResult::Value(nb)),
        Err(_) => client.handle_response(response).await,
    }
}
