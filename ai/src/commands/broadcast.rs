//
// EPITECH PROJECT, 2024
// broadcast
// File description:
// broadcast command
//

#![allow(dead_code)]

use std::sync::Arc;
use crate::tcp::TcpClient;

pub async fn broadcast(client: Arc<TcpClient>, msg: &str) -> std::io::Result<()> {
    client.clone().write_stream(String::from("Broadcast ") + msg + "\n").await?;

    match client.clone().read_stream().await {
        Ok(res) => print!("{res}"),
        Err(_) => {},
    }

    Ok(())
}
