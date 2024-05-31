//
// EPITECH PROJECT, 2024
// drop_object
// File description:
// set object command
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

use log::info;

pub async fn drop_object(client: &mut TcpClient, obj: &str) -> Result<bool, bool> {
    info!("Dropping object: ({})...", obj);
    let response = client.check_dead(&format!("Set {}\n", obj)).await?;
    client.handle_response(response).await
}
