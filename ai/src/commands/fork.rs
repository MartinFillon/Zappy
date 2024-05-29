//
// EPITECH PROJECT, 2024
// fork
// File description:
// fork command
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

pub async fn fork(client: &mut TcpClient) -> bool {
    match client.check_dead("Fork\n").await {
        Ok(_) => true,
        Err(_) => false,
    }
}
