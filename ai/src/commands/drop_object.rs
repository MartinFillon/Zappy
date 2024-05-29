//
// EPITECH PROJECT, 2024
// drop_object
// File description:
// set object command
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

pub async fn drop_object(client: &mut TcpClient, obj: &str) -> Result<bool, bool> {
    let response = client.check_dead(&format!("Set {}\n", obj)).await?;
    match response.as_str() {
        "ok\n" => Ok(true),
        _ => Ok(false),
    }
}
