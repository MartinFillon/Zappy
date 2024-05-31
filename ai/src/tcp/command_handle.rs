//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// commands
//

#![allow(dead_code)]

// use crate::commands;
use crate::tcp::TcpClient;

use async_trait::async_trait;

use tokio::io::{self};

use std::io::{Error, ErrorKind};

use log::info;

enum Direction {
    North,
    NorthWest,
    West,
    SouthWest,
    South,
    SouthEast,
    East,
    NorthEast
}

enum ResponseResult {
    ok,
    ko,
    dead,
    Value(i32),
    Text(String),
    Tiles(Vec<String>),
    Inventory(Vec<String>),
    Incantation(i32),
    Message((Direction, String))
}

#[async_trait]
pub trait CommandHandler {
    async fn send_command(&mut self, command: &str) -> Result<String, bool>;
    async fn check_dead(&mut self, command: &str) -> Result<String, bool>;
    async fn handle_response(&mut self, response: String) -> Result<bool, bool>;
}

#[async_trait::async_trait]
impl CommandHandler for TcpClient {
    async fn send_command(&mut self, command: &str) -> Result<String, bool> {
        info!("Sending command: ({})...", command);
        if self.send_request(command.to_string()).await.is_err() {
            return Err(true);
        }
        match self.get_response().await {
            Some(res) => Ok(res),
            None => Err(true),
        }
    }

    async fn check_dead(&mut self, command: &str) -> Result<String, bool> {
        info!("Checking if request receives dead...");
        let response = self.send_command(command).await?;
        if response == "dead\n" {
            info!("Dead received.");
            return Err(false);
        }
        info!("Not dead received, response is forwarded.");
        Ok(response)
    }

    async fn handle_response(&mut self, response: String) -> Result<bool, bool> {
        info!("Handling response: ({})...", response);
        match response.as_str() {
            "ok\n" => Ok(true),
            "ko\n" => Ok(false),
            _ => Err(false),
        }
    }
}

pub async fn start_ai(mut client: TcpClient, team: String) -> io::Result<()> {
    client.send_request(team + "\n").await?;
    if let Some(response) = client.get_response().await {
        print!("server> {}", response);
    } else {
        return Err(Error::new(
            ErrorKind::ConnectionRefused,
            "Couldn't reach host.",
        ));
    }
    Ok(())
}
