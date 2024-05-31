//
// EPITECH PROJECT, 2024
// fork
// File description:
// fork command
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

use log::info;

pub async fn fork(client: &mut TcpClient) -> bool {
    info!("Forking...");
    client.check_dead("Fork\n").await.is_ok()
}
