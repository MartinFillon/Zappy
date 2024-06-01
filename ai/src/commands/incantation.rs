//
// EPITECH PROJECT, 2024
// incantation
// File description:
// incantation command
//

#![allow(dead_code)]

use crate::tcp::command_handle::{CommandError, CommandHandler, ResponseResult};
use crate::tcp::TcpClient;

pub async fn incantation(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    let checkpoint = client.check_dead("Incantation\n").await?;
    match checkpoint.trim_end() {
        "ko" => Ok(ResponseResult::KO),
        "Elevation underway" => {
            let response = client
                .get_response()
                .await
                .ok_or(CommandError::NoResponseReceived)?;
            match response.trim_end() {
                "ko" => Ok(ResponseResult::KO),
                "dead" => Err(CommandError::DeadReceived),
                level if level.starts_with("Current level:") => {
                    let level_str = level
                        .split_once(": ")
                        .and_then(|(_, l)| l.parse::<usize>().ok())
                        .ok_or(CommandError::InvalidResponse)?;
                    Ok(ResponseResult::Incantation(level_str))
                }
                _ => Err(CommandError::InvalidResponse),
            }
        }
        _ => Err(CommandError::InvalidResponse),
    }
}
