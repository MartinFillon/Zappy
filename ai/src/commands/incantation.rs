//
// EPITECH PROJECT, 2024
// incantation
// File description:
// incantation command
//

#![allow(dead_code)]

use crate::tcp::{
    command_handle::{CommandError, CommandHandler, ResponseResult},
    TcpClient,
};

use log::debug;

pub fn get_current_level(level_str: &str) -> Result<usize, CommandError> {
    level_str
        .split_once(": ")
        .and_then(|(_, l)| l.parse::<usize>().ok())
        .ok_or(CommandError::InvalidResponse)
}

pub async fn handle_incantation(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    let response = client
        .get_response()
        .await
        .ok_or(CommandError::NoResponseReceived)?;
    match response.trim_end() {
        "dead" => Err(CommandError::DeadReceived),
        level if level.starts_with("Current level: ") => {
            let level_str = get_current_level(level)?;
            Ok(ResponseResult::Incantation(level_str))
        }
        _ => client.handle_response(response).await,
    }
}

pub async fn incantation(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    debug!("Incantation...");

    let checkpoint = client.check_dead("Incantation\n").await?;
    match checkpoint.trim_end() {
        "Elevation underway" => handle_incantation(client).await,
        _ => client.handle_response(checkpoint).await,
    }
}
