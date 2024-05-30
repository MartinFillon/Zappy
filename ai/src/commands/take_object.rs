//
// EPITECH PROJECT, 2024
// take_object
// File description:
// take object command
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

pub async fn take_object(client: &mut TcpClient, obj: &str) -> Result<bool, bool> {
    let response = client.check_dead(&format!("Take {}\n", obj)).await?;
    client.handle_response(response).await
}
