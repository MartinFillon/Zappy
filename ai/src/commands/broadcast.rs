//
// EPITECH PROJECT, 2024
// broadcast
// File description:
// broadcast command
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

use log::info;

pub async fn broadcast(client: &mut TcpClient, msg: &str) -> bool {
    info!("Broadcasting: ({})...", msg);
    client
        .check_dead(&format!("Broadcast {}\n", msg))
        .await
        .is_ok()
}
