//
// EPITECH PROJECT, 2024
// ai.rs
// File description:
// zappy ai main functions
//

#![allow(dead_code)]
// #![allow(unused_imports)]

pub mod bot;
pub mod fetus;
pub mod knight;
pub mod queen;

use crate::commands;
use crate::tcp::command_handle::Direction;
use crate::tcp::{self, TcpClient};

use std::fmt;
use std::fmt::{Display, Formatter};
use std::io::{self, Error, ErrorKind};
use std::sync::Arc;

use tokio::task;

use log::{debug, info};

#[derive(Debug, Clone)]
enum AIState {
    Bot,
    Queen,
    Knight,
    Fetus,
}

pub enum Action {
    Movement((i32, i32)),
    Push(Direction),
    LevelUp,
}

#[derive(Debug, Clone)]
pub struct AI {
    team: String,
    client: i32,
    map: (usize, usize),
    level: usize,
    state: Option<AIState>,
}

pub trait AIHandler {
    fn init(&mut self, info: AI) -> Self;
    fn update(&mut self, action: Option<Action>);
}

impl Display for AIState {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        match self {
            AIState::Bot => write!(f, "Bot"),
            AIState::Queen => write!(f, "Queen"),
            AIState::Knight => write!(f, "Knight"),
            AIState::Fetus => write!(f, "Fetus"),
        }
    }
}

impl AI {
    fn new(
        team: String,
        client: i32,
        map: (usize, usize),
        level: usize,
        state: Option<AIState>,
    ) -> Self {
        Self {
            team,
            client,
            map,
            level,
            state,
        }
    }
}

impl Display for AI {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(
            f,
            "AI {} = [team: {}, client: {}, map: ({}, {}), level: {}]",
            <Option<AIState> as Clone>::clone(&self.state)
                .map_or_else(|| String::from("None"), |p| p.to_string()),
            self.team,
            self.client,
            self.map.0,
            self.map.1,
            self.level
        )
    }
}

async fn startup_commands(client: &mut TcpClient) -> io::Result<()> {
    info!("Sending startup commands...");
    match commands::inventory::inventory(client).await {
        Ok(res) => {
            info!("Inventory checked.");
            println!("{}", res);
        }
        Err(_) => return Err(Error::new(ErrorKind::InvalidData, "Invalid response.")),
    }
    Ok(())
}

async fn init_ai(client: &mut TcpClient, response: &str, team: String) -> io::Result<()> {
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
            let ai: AI = AI::new(team, client_number, (x, y), 1, None);
            println!("({})> {}", client_number, ai);
            info!("{}", ai);
            info!("AI initialized.");
        }
        None => return Err(Error::new(ErrorKind::InvalidData, "Invalid response.")),
    }
    startup_commands(client).await?;
    Ok(())
}

async fn start_ai(mut client: TcpClient, team: String) -> io::Result<()> {
    info!("Starting AI...");
    client.send_request(team.clone() + "\n").await?;
    if let Some(response) = client.get_response().await {
        match response.trim_end() {
            "ko" => {
                print!("server> {}", response);
                return Err(Error::new(
                    ErrorKind::ConnectionRefused,
                    "No room for player.",
                ));
            }
            _ => init_ai(&mut client, &response, team).await?,
        }
    } else {
        return Err(Error::new(
            ErrorKind::ConnectionRefused,
            "Couldn't reach host.",
        ));
    }
    Ok(())
}

pub async fn launch(address: String, team: String) -> io::Result<()> {
    let mut handles = vec![];

    let team = Arc::new(team);
    loop {
        match tcp::handle_tcp(address.clone()).await {
            Ok(client) => {
                let team: Arc<String> = Arc::clone(&team);
                let handle = task::spawn(async move {
                    let team_str = &*team;
                    match start_ai(client, team_str.clone()).await {
                        Ok(_) => {
                            println!("ok");
                            Ok(())
                        }
                        Err(e) => {
                            println!("ko");
                            Err(e)
                        }
                    }
                });
                handles.push(handle);
            }
            Err(e) => {
                println!("Failed to handle TCP: {}", e);
                break;
            }
        }
    }

    if handles.is_empty() {
        debug!("Connection refused, handles is empty.");
        return Err(Error::new(
            ErrorKind::ConnectionRefused,
            "Couldn't reach host.",
        ));
    }

    Ok(())
}
