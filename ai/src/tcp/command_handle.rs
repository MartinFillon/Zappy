//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// commands
//

#![allow(dead_code)]

use crate::tcp::TcpClient;

use async_trait::async_trait;

use std::fmt;
use std::fmt::{Display, Formatter};

use log::{debug, info};

pub enum ResponseResult {
    OK,
    KO,
    Dead,
    Value(usize),
    Text(String),
    Tiles(Vec<Vec<String>>),
    Inventory(Vec<(String, i32)>),
    Incantation(usize),
    Message((Direction, String)),
    Eject(Direction),
}

#[derive(Debug, PartialEq)]
#[repr(u8)]
pub enum Direction {
    Center,
    North,
    NorthWest,
    West,
    SouthWest,
    South,
    SouthEast,
    East,
    NorthEast,
}

pub enum CommandError {
    RequestError,
    NoResponseReceived,
    InvalidResponse,
    DeadReceived,
}

#[async_trait]
pub trait CommandHandler {
    async fn send_command(&mut self, command: &str) -> Result<String, CommandError>;
    async fn check_dead(&mut self, command: &str) -> Result<String, CommandError>;
    async fn handle_response(&mut self, response: String) -> Result<ResponseResult, CommandError>;
}

#[async_trait::async_trait]
impl CommandHandler for TcpClient {
    async fn send_command(&mut self, command: &str) -> Result<String, CommandError> {
        info!("Sending command: ({})...", command.trim_end());
        if self.send_request(command.to_string()).await.is_err() {
            return Err(CommandError::RequestError);
        }
        match self.get_response().await {
            Some(res) => Ok(res),
            None => Err(CommandError::NoResponseReceived),
        }
    }

    async fn check_dead(&mut self, command: &str) -> Result<String, CommandError> {
        info!("Checking if request receives dead...");
        let response: String = self.send_command(command).await?;
        if response == "dead\n" {
            debug!("Dead received.");
            return Err(CommandError::DeadReceived);
        }
        info!("Dead not received, response is forwarded.");
        Ok(response)
    }

    async fn handle_response(&mut self, response: String) -> Result<ResponseResult, CommandError> {
        info!("Handling response: ({})...", response.trim_end());

        if response.starts_with("message ") && response.ends_with('\n') {
            return handle_message_response(response);
        }

        if response.starts_with("eject: ") && response.ends_with('\n') {
            return handle_eject_response(response);
        }

        match response.trim_end() {
            "ok" => Ok(ResponseResult::OK),
            "ko" => Ok(ResponseResult::KO),
            _ => Err(CommandError::InvalidResponse),
        }
    }
}

fn handle_message_response(response: String) -> Result<ResponseResult, CommandError> {
    info!("Handling message response...");
    let parts: Vec<&str> = response.split_whitespace().collect();

    if parts.len() >= 3 && parts[0] == "message" {
        match parts[1].trim_end_matches(',').parse::<usize>() {
            Ok(direction) => {
                if let Some(dir_enum) = Direction::from_usize(direction) {
                    let final_msg = parts[2..].join(" ");
                    info!(
                        "Message received from direction {} (aka {}): {}",
                        dir_enum, direction, final_msg
                    );
                    return Ok(ResponseResult::Message((dir_enum, final_msg)));
                }
                debug!("Failed to parse direction {}.", direction);
            }
            Err(_) => debug!("Failed to parse direction from message: {}", response),
        }
    }

    Err(CommandError::InvalidResponse)
}

fn handle_eject_response(response: String) -> Result<ResponseResult, CommandError> {
    info!("Handling eject response...");
    let parts: Vec<&str> = response.split_whitespace().collect();

    if parts.len() == 2 && parts[0] == "eject:" {
        match parts[1].trim_start().parse::<usize>() {
            Ok(direction) => {
                if let Some(dir_enum) = Direction::from_usize(direction) {
                    info!(
                        "Receiving ejection from direction {} (aka {}).",
                        dir_enum, direction
                    );
                    return Ok(ResponseResult::Eject(dir_enum));
                }
                debug!("Failed to parse direction {}.", direction);
            }
            Err(_) => debug!(
                "Failed to parse direction from eject response: {}",
                response
            ),
        }
    }

    Err(CommandError::InvalidResponse)
}

impl Direction {
    pub fn to_usize(&self) -> usize {
        match self {
            Direction::Center => 0,
            Direction::North => 1,
            Direction::NorthWest => 2,
            Direction::West => 3,
            Direction::SouthWest => 4,
            Direction::South => 5,
            Direction::SouthEast => 6,
            Direction::East => 7,
            Direction::NorthEast => 8,
        }
    }

    pub fn from_usize(value: usize) -> Option<Self> {
        match value {
            0 => Some(Direction::Center),
            1 => Some(Direction::North),
            2 => Some(Direction::NorthWest),
            3 => Some(Direction::West),
            4 => Some(Direction::SouthWest),
            5 => Some(Direction::South),
            6 => Some(Direction::SouthEast),
            7 => Some(Direction::East),
            8 => Some(Direction::NorthEast),
            _ => None,
        }
    }
}

impl Display for CommandError {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        match self {
            CommandError::RequestError => write!(f, "Request error."),
            CommandError::NoResponseReceived => write!(f, "No response received."),
            CommandError::InvalidResponse => write!(f, "Invalid response."),
            CommandError::DeadReceived => write!(f, "Dead received."),
        }
    }
}

impl Display for Direction {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        match self {
            Direction::Center => write!(f, "Center"),
            Direction::North => write!(f, "North"),
            Direction::NorthWest => write!(f, "NorthWest"),
            Direction::West => write!(f, "West"),
            Direction::SouthWest => write!(f, "SouthWest"),
            Direction::South => write!(f, "South"),
            Direction::SouthEast => write!(f, "SouthEast"),
            Direction::East => write!(f, "East"),
            Direction::NorthEast => write!(f, "NorthEast"),
        }
    }
}

impl Display for ResponseResult {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        match self {
            ResponseResult::OK => write!(f, "OK"),
            ResponseResult::KO => write!(f, "KO"),
            ResponseResult::Dead => write!(f, "Dead"),
            ResponseResult::Value(nb) => write!(f, "Value: {}", nb),
            ResponseResult::Text(text) => write!(f, "Text: {}", text),
            ResponseResult::Tiles(tiles) => {
                write!(f, "Tiles: [")?;
                for (i, tile) in tiles.iter().enumerate() {
                    write!(f, "[")?;
                    for (j, item) in tile.iter().enumerate() {
                        if j + 1 == tile.len() {
                            write!(f, "{}", item)?;
                        } else {
                            write!(f, "{}, ", item)?;
                        }
                    }
                    if i + 1 == tiles.len() {
                        write!(f, "]")?;
                    } else {
                        write!(f, "], ")?;
                    }
                }
                write!(f, "]")
            }
            ResponseResult::Inventory(inventory) => {
                write!(f, "Inventory: [")?;
                for (i, (item, nb)) in inventory.iter().enumerate() {
                    if i + 1 == inventory.len() {
                        write!(f, "({}: x{})", item, nb)?;
                    } else {
                        write!(f, "({}: x{}), ", item, nb)?;
                    }
                }
                write!(f, "]")
            }
            ResponseResult::Incantation(level) => write!(f, "Incantation Level: {}", level),
            ResponseResult::Message((dir, msg)) => write!(f, "Message: ({}, {})", dir, msg),
            ResponseResult::Eject(dir) => write!(f, "Eject: {}", dir),
        }
    }
}
