//
// EPITECH PROJECT, 2024
// incantation
// File description:
// incantation command
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

pub async fn incantation(client: &mut TcpClient) -> Result<Option<usize>, bool> {
    let res1 = client.check_dead("Incantation\n").await?;
    match res1.as_str() {
        "ko\n" => Ok(None),
        "Elevation underway\n" => {
            if let Some(res2) = client.get_response().await {
                match res2.as_str() {
                    "ko\n" => Ok(None),
                    "dead\n" => Err(false),
                    level if res2.starts_with("Current level:") => match level
                        .trim_end()
                        .split_once(": ")
                        .unwrap_or_default()
                        .1
                        .parse::<usize>()
                    {
                        Ok(k) => Ok(Some(k)),
                        Err(_) => Err(true),
                    },
                    _ => Err(true),
                }
            } else {
                Err(true)
            }
        }
        _ => Err(true),
    }
}
