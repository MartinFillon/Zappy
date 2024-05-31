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

use std::fmt::Display;
use std::io::{Error, ErrorKind};

use log::{debug, info};

pub enum ResponseResult {
    OK,
    KO,
    Dead,
    Value(usize),
    Text(String),
    Tiles(Vec<String>),
    Inventory(Vec<(String, i32)>),
    Incantation(usize),
    Message((Direction, String)),
}

pub enum Direction {
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
        info!("Sending command: ({})...", command);
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
        let response = self.send_command(command).await?;
        if response == "dead\n" {
            info!("Dead received.");
            return Err(CommandError::DeadReceived);
        }
        info!("Not dead received, response is forwarded.");
        Ok(response)
    }

    async fn handle_response(&mut self, response: String) -> Result<ResponseResult, CommandError> {
        info!("Handling response: ({})...", response);
        match response.as_str() {
            "ok\n" => Ok(ResponseResult::OK),
            "ko\n" => Ok(ResponseResult::KO),
            _ => Err(CommandError::InvalidResponse),
        }
    }
}

impl Display for CommandError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            CommandError::RequestError => write!(f, "Request error."),
            CommandError::NoResponseReceived => write!(f, "No response received."),
            CommandError::InvalidResponse => write!(f, "Invalid response."),
            CommandError::DeadReceived => write!(f, "Dead received."),
        }
    }
}

impl Display for Direction {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
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
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            ResponseResult::OK => write!(f, "OK"),
            ResponseResult::KO => write!(f, "KO"),
            ResponseResult::Dead => write!(f, "Dead"),
            ResponseResult::Value(nb) => write!(f, "Value: {}", nb),
            ResponseResult::Text(text) => write!(f, "Text: {}", text),
            ResponseResult::Tiles(tiles) => {
                write!(f, "Tiles: [")?;
                for tile in tiles {
                    write!(f, "{}, ", tile)?;
                }
                write!(f, "]")
            }
            ResponseResult::Inventory(inventory) => {
                write!(f, "Inventory: [")?;
                for (item, nb) in inventory {
                    write!(f, "({}: x{}), ", item, nb)?;
                }
                write!(f, "]")
            }
            ResponseResult::Incantation(level) => write!(f, "Incantation Level: {}", level),
            ResponseResult::Message((dir, msg)) => write!(f, "Message: ({}, {})", dir, msg),
        }
    }
}

struct AI {
    client: i32,
    map: (usize, usize),
    level: usize,
    // state: String
}

impl AI {
    fn new(client_number: i32, map_x: usize, map_y: usize) -> AI {
        AI {
            client: client_number,
            map: (map_x, map_y),
            level: 1,
        }
    }
}

impl Display for AI {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "AI: [client: {}, map: ({}, {}), level: {}]",
            self.client, self.map.0, self.map.1, self.level
        )
    }
}

async fn init_ai(_client: &mut TcpClient, response: &str) -> io::Result<()> {
    info!("Initializing AI...");
    let mut lines = response.split('\n');

    let client_number = match lines.next() {
        Some(nbr) => match nbr.parse::<i32>() {
            Ok(nbr) => nbr,
            Err(_) => return Err(Error::new(ErrorKind::InvalidData, "Invalid client number.")),
        },
        None => return Err(Error::new(ErrorKind::InvalidData, "Invalid response.")),
    };
    info!("Client number detected as [{}].", client_number);

    match lines.next() {
        Some(line) => {
            let mut words = line.split_whitespace();
            let x = match words.next().and_then(|word| word.parse::<usize>().ok()) {
                Some(val) => val,
                None => {
                    debug!("Failed to parse x coordinate from line: {}", line);
                    return Err(Error::new(ErrorKind::InvalidData, "Invalid x coordinate."));
                }
            };
            let y = match words.next().and_then(|word| word.parse::<usize>().ok()) {
                Some(val) => val,
                None => {
                    debug!("Failed to parse y coordinate from line: {}", line);
                    return Err(Error::new(ErrorKind::InvalidData, "Invalid y coordinate."));
                }
            };
            info!("Map size: ({}, {}).", x, y);
            let ai: AI = AI::new(client_number, x, y);
            println!("{}", ai);
            info!("{}", ai);
            info!("AI initialized.");
        }
        None => return Err(Error::new(ErrorKind::InvalidData, "Invalid response.")),
    }
    Ok(())
}

#[warn(unused_mut)]
pub async fn start_ai(mut client: TcpClient, team: String) -> io::Result<()> {
    info!("Starting AI...");
    client.send_request(team + "\n").await?;
    if let Some(response) = client.get_response().await {
        match response.trim_end() {
            "ko" => {
                print!("server> {}", response);
                return Err(Error::new(
                    ErrorKind::ConnectionRefused,
                    "No room for player.",
                ));
            }
            _ => init_ai(&mut client, &response).await?,
        }
    } else {
        return Err(Error::new(
            ErrorKind::ConnectionRefused,
            "Couldn't reach host.",
        ));
    }
    Ok(())
}
