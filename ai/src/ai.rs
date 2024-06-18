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

use crate::tcp::{
    self,
    command_handle::{CommandError, ResponseResult},
    TcpClient,
};

use std::fmt;
use std::fmt::{Display, Formatter};
use std::io::{self, Error, ErrorKind};
use std::sync::{
    atomic::{AtomicBool, AtomicUsize, Ordering},
    Arc,
};

use async_trait::async_trait;
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

#[async_trait]
pub trait AIHandler {
    fn init(info: AI) -> Self;
    async fn update(&mut self) -> Result<(), CommandError>;
    async fn fork_dupe(info: AI, set_id: Option<usize>) -> io::Result<()>;
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
        0..=3 => {
            let mut queen = queen::Queen::init(ai.clone());
            if let Err(e) = queen.update().await {
                error!("Error: {}", e);
            }
        }
        _ => {
            let mut bot = bot::Bot::init(ai.clone());
            if let Err(e) = bot.update().await {
                error!("Error: {}", e);
            }
        }
    }
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

async fn handle_client(
    client: Arc<Mutex<TcpClient>>,
    team: Arc<String>,
    address: Arc<String>,
    id: usize,
    stop_flag: Arc<AtomicBool>,
) -> io::Result<()> {
    let result = start_ai(client, team.to_string(), address.to_string(), (id, 0), true).await;

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
}

async fn launch_connections(
    address: Arc<String>,
    team: Arc<String>,
    connection_id: Arc<AtomicUsize>,
    stop_flag: Arc<AtomicBool>,
) {
    loop {
        if stop_flag.load(Ordering::SeqCst) {
            println!("Stop flag is set, breaking the loop.");
            break;
        }

        match tcp::handle_tcp(address.to_string(), team.to_string()).await {
            Ok(client) => {
                let address = Arc::clone(&address);
                let client = Arc::new(Mutex::new(client));
                let id = connection_id.fetch_add(1, Ordering::SeqCst);
                let stop_flag = Arc::clone(&stop_flag);
                tokio::spawn(handle_client(client, team.clone(), address, id, stop_flag));
            }
            Err(e) => {
                println!("Failed to handle TCP: {}", e);
                break;
            }
        }
    }
}

// pub async fn launch(address: String, team: String) -> io::Result<()> {
//     let team = Arc::new(team);
//     let address = Arc::new(address);
//     let connection_id = Arc::new(AtomicUsize::new(0));
//     let stop_flag = Arc::new(AtomicBool::new(false));

//     let launch_task = tokio::spawn(launch_connections(
//         Arc::clone(&address),
//         Arc::clone(&team),
//         Arc::clone(&connection_id),
//         Arc::clone(&stop_flag),
//     ));

//     if let Err(e) = launch_task.await {
//         println!("Launch task failed: {:?}", e);
//     }

//     Ok(())
// }

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
