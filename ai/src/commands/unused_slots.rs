//
// EPITECH PROJECT, 2024
// unused_slots
// File description:
// connect_nbr command
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

use log::info;

pub async fn unused_slots(client: &mut TcpClient) -> Result<usize, bool> {
    info!("Checking unused slots...");
    let response = client.check_dead("Connect_nbr\n").await?;
    match response.parse::<usize>() {
        Ok(nb) => Ok(nb),
        Err(_) => Err(true),
    }
}
