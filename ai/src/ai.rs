//
// EPITECH PROJECT, 2024
// ai.rs
// File description:
// zappy ai main functions
//

#![allow(dead_code)]

pub mod bot;
pub mod empress;
pub mod fetus;
pub mod knight;
pub mod queen;

use crate::{
    commands::broadcast,
    tcp::{
        self,
        command_handle::{CommandError, ResponseResult},
        handle_tcp, TcpClient,
    },
};

use std::fmt;
use std::fmt::{Display, Formatter};
use std::io::{self, Error, ErrorKind};
use std::sync::{
    atomic::{AtomicBool, AtomicUsize, Ordering},
    Arc,
};

use async_trait::async_trait;
use empress::Empress;
use fetus::Fetus;
use knight::Knight;
use queen::Queen;
use tokio::{sync::Mutex, task};

use log::{debug, error, info, warn};
use zappy_macros::Bean;

#[derive(Debug, Clone, Bean)]
pub struct AI {
    address: String,
    team: String,
    cli_id: usize,
    p_id: usize,
    client: Arc<Mutex<TcpClient>>,
    map: (i32, i32),
    level: usize,
}

#[derive(Debug, Clone)]
enum Roles {
    Empress,
    Fetus,
    Knight,
    Queen,
}

impl TryFrom<String> for Roles {
    type Error = String;

    fn try_from(value: String) -> Result<Self, Self::Error> {
        match value.as_str() {
            "Empress" => Ok(Self::Empress),
            "Fetus" => Ok(Self::Fetus),
            "Knight" => Ok(Self::Knight),
            "Queen" => Ok(Self::Queen),
            _ => Err(format!("Unknown role: {}", value)),
        }
    }
}

impl Display for Roles {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        match *self {
            Self::Empress => write!(f, "Empress"),
            Self::Fetus => write!(f, "Fetus"),
            Self::Knight => write!(f, "Knight"),
            Self::Queen => write!(f, "Queen"),
        }
    }
}

async fn send_role(client: &mut TcpClient, role: Roles) -> Result<ResponseResult, CommandError> {
    broadcast::broadcast(client, role.to_string().as_str()).await
}

fn init_from_broadcast(info: &AI, role: String) -> Result<Box<dyn AIHandler>, String> {
    Ok(match Roles::try_from(role)? {
        Roles::Empress => Box::new(Empress::init(info.clone())),
        Roles::Fetus => Box::new(Fetus::init(info.clone())),
        Roles::Knight => Box::new(Knight::init(info.clone())),
        Roles::Queen => Box::new(Queen::init(info.clone())),
    })
}

pub async fn new_fork_dupe(info: AI, set_id: Option<usize>) -> io::Result<()> {
    let client: Arc<Mutex<TcpClient>> =
        match handle_tcp(info.address.clone(), info.team.clone()).await {
            Ok(client) => {
                debug!("New `Bot` client connected successfully.");
                Arc::new(Mutex::new(client))
            }
            Err(e) => return Err(Error::new(e.kind(), e)),
        };

    let c_id = info.cli_id;
    let p_id = set_id.unwrap_or(0);
    let team = info.team.clone();
    let address = info.address.clone();

    let handle = task::spawn(async move {
        match start_ai(client, team, address, (c_id, p_id), false).await {
            Ok(ai) => {
                let mut rle = init_from_broadcast(&info, String::from("Bot"))
                    .map_err(|e| std::io::Error::new(ErrorKind::NotFound, e))?;
                if let Err(e) = rle.update().await {
                    println!("Error: {}", e);
                }
                Ok(ai)
            }
            Err(e) => {
                error!("{}", e);
                Err(e)
            }
        }
    });

    tokio::spawn(async move {
        if let Err(e) = handle.await {
            error!("Task failed: {:?}", e);
        }
    });

    Ok(())
}

#[async_trait]
pub trait AIHandler: Send {
    fn init(info: AI) -> Self
    where
        Self: Sized;
    async fn update(&mut self) -> Result<(), CommandError>;
    async fn fork_dupe(info: AI, set_id: Option<usize>) -> io::Result<()>
    where
        Self: Sized;
}

#[async_trait]
pub trait Incantationers {
    async fn handle_eject(
        client: &mut TcpClient,
        res: Result<ResponseResult, CommandError>,
    ) -> Result<ResponseResult, CommandError>;

    async fn handle_elevating(
        client: &mut TcpClient,
        res: Result<ResponseResult, CommandError>,
    ) -> Result<ResponseResult, CommandError>;
}

#[async_trait]
pub trait Listeners {
    async fn handle_message(&mut self) -> Result<ResponseResult, CommandError>;
}

impl AI {
    fn new(
        team: String,
        address: String,
        cli_id: usize,
        p_id: usize,
        client: Arc<Mutex<TcpClient>>,
        map: (i32, i32),
        level: usize,
    ) -> Self {
        Self {
            team,
            address,
            cli_id,
            p_id,
            client,
            map,
            level,
        }
    }
}

impl Display for AI {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(
            f,
            "AI #{} = [team: {}, player ID: {}, map: ({}, {}), level: {}]",
            self.cli_id, self.team, self.p_id, self.map.0, self.map.1, self.level
        )
    }
}

async fn parse_response(
    response: &str,
    client: Arc<Mutex<TcpClient>>,
) -> Result<(i32, i32, i32), io::Error> {
    let mut cli = client.lock().await;
    let client_number = response
        .parse::<i32>()
        .map_err(|_| Error::new(ErrorKind::InvalidData, "Invalid client number."))?;

    let response = cli
        .get_response()
        .await
        .ok_or_else(|| Error::new(ErrorKind::InvalidData, "Invalid response."))?;

    let mut words = response.split_whitespace();
    let x = words
        .next()
        .and_then(|word| word.parse::<i32>().ok())
        .ok_or_else(|| Error::new(ErrorKind::InvalidData, "Invalid x coordinate."))?;
    let y = words
        .next()
        .and_then(|word| word.parse::<i32>().ok())
        .ok_or_else(|| Error::new(ErrorKind::InvalidData, "Invalid y coordinate."))?;
    Ok((client_number, x, y))
}

async fn checkout_ai_info(
    client: Arc<Mutex<TcpClient>>,
    response: &str,
    team: String,
    address: String,
    (c_id, p_id): (usize, usize),
) -> io::Result<AI> {
    parse_response(response, client.clone())
        .await
        .map(|(client_number, x, y)| {
            info!("Client number detected as [{}].", client_number);
            info!("Map size: ({}, {}).", x, y);
            let ai = AI::new(team, address, c_id, p_id, client.clone(), (x, y), 1);
            println!("New! >> {}", ai);
            info!("AI #{} is initialized.", ai.cli_id);
            ai
        })
        .map_err(|e| {
            debug!("Failed to parse response: {}", e);
            e
        })
}

async fn init_ai(
    client: Arc<Mutex<TcpClient>>,
    response: &str,
    team: String,
    address: String,
    (c_id, p_id): (usize, usize),
) -> io::Result<AI> {
    info!("Initializing AI #{}...", c_id);

    let ai = checkout_ai_info(client, response, team, address, (c_id, p_id)).await?;
    match ai.cli_id {
        0 => {
            let mut empress = empress::Empress::init(ai.clone());
            if let Err(e) = empress.update().await {
                println!("Error: {}", e);
            }
        }
        _ => {
            let mut fetus = fetus::Fetus::init(ai.clone());
            if let Err(e) = fetus.update().await {
                println!("Error: {}", e);
            }
        }
    };
    Ok(ai)
}

async fn start_ai(
    client: Arc<Mutex<TcpClient>>,
    team: String,
    address: String,
    (c_id, p_id): (usize, usize),
    start: bool,
) -> io::Result<AI> {
    println!("Starting AI process n{}...", c_id);
    {
        let client_lock = client.lock().await;
        client_lock.send_request(team.clone() + "\n").await?;
    }
    if let Some(response) = {
        let mut client_lock = client.lock().await;
        client_lock.get_response().await
    } {
        match response.trim_end() {
            "ko" => {
                print!("server> {}", response);
                debug!("Server doesn't handle any more connection.");
                Err(Error::new(
                    ErrorKind::ConnectionRefused,
                    "No room for player.",
                ))
            }
            _ => {
                info!("Connection to team successful.");
                let ai = match start {
                    true => init_ai(client.clone(), &response, team, address, (c_id, p_id)).await?,
                    false => {
                        checkout_ai_info(client.clone(), &response, team, address, (c_id, p_id))
                            .await?
                    }
                };
                Ok(ai)
            }
        }
    } else {
        debug!("Host not reachable.");
        Err(Error::new(
            ErrorKind::ConnectionRefused,
            "Couldn't reach host.",
        ))
    }
}

pub async fn launch(address: String, team: String) -> io::Result<()> {
    let mut handles = vec![];
    let team = Arc::new(team);
    let address = Arc::new(address);
    let connection_id = Arc::new(AtomicUsize::new(0));
    let stop_flag = Arc::new(AtomicBool::new(false));

    loop {
        if stop_flag.load(Ordering::SeqCst) {
            println!("Stop flag is set, breaking the loop.");
            break;
        }
        let team = Arc::clone(&team);

        match tcp::handle_tcp(address.to_string(), team.to_string()).await {
            Ok(client) => {
                let address = Arc::clone(&address);
                let client = Arc::new(Mutex::new(client));
                let id = connection_id.fetch_add(1, Ordering::SeqCst);
                let stop_flag = Arc::clone(&stop_flag);

                let handle = task::spawn(async move {
                    let result = start_ai(
                        client.clone(),
                        team.to_string(),
                        address.to_string(),
                        (id, 0),
                        true,
                    )
                    .await;

                    match result {
                        Ok(_) => {
                            println!("Connection {} handled successfully", id);
                            Ok(())
                        }
                        Err(e) => {
                            println!("Connection {} failed: {}", id, e);
                            stop_flag.store(true, Ordering::SeqCst);
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
        warn!("Connection refused, handles is empty.");
        return Err(Error::new(
            ErrorKind::ConnectionRefused,
            "Couldn't reach host.",
        ));
    }

    for handle in handles {
        if let Err(e) = handle.await {
            println!("Task failed: {:?}", e);
        }
    }

    Ok(())
}
