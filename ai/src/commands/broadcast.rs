//
// EPITECH PROJECT, 2024
// broadcast
// File description:
// broadcast command
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

pub async fn broadcast(client: &mut TcpClient, msg: &str) -> bool {
    match client.check_dead(&format!("Broadcast {}\n", msg)).await {
        Ok(_) => true,
        Err(_) => false,
    }
}
