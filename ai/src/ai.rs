//
// EPITECH PROJECT, 2024
// ai.rs
// File description:
// zappy ai main functions
//

#![allow(dead_code)]
#![allow(unused_imports)]
#![allow(unused_mut)]

pub mod bot;
pub mod empress;
pub mod fetus;
pub mod knight;
pub mod queen;

use crate::{
    commands,
    tcp::{
        self,
        command_handle::{CommandError, ResponseResult},
        TcpClient,
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
use tokio::{sync::Mutex, task};

use log::{debug, info, warn};
use zappy_macros::Bean;

#[derive(Debug, Clone, Bean)]
pub struct AI {
    team: String,
    cli_id: i32,
    p_id: usize,
    client: Arc<Mutex<TcpClient>>,
    map: (i32, i32),
    level: usize,
}

#[async_trait]
pub trait AIHandler {
    fn init(info: AI) -> Self;
    async fn update(&mut self) -> Result<(), CommandError>;
}

#[async_trait]
pub trait Incantationers {
    async fn handle_eject(
        client: &mut TcpClient,
        res: Result<ResponseResult, CommandError>,
    ) -> Result<ResponseResult, CommandError>;
}

#[async_trait]
pub trait Listeners {
    async fn handle_message(
        client: &mut TcpClient,
        res: Result<ResponseResult, CommandError>,
    ) -> Result<ResponseResult, CommandError>;
}

impl AI {
    fn new(
        team: String,
        cli_id: i32,
        p_id: usize,
        client: Arc<Mutex<TcpClient>>,
        map: (i32, i32),
        level: usize,
    ) -> Self {
        Self {
            team,
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
            "AI #{} = [team: {}, client: {}, map: ({}, {}), level: {}]",
            self.p_id, self.team, self.cli_id, self.map.0, self.map.1, self.level
        )
    }
}

// test here
#[allow(dead_code)]
async fn kickstart(ai: AI) -> io::Result<AI> {
    info!("Sending startup commands...");

    let mut empress = empress::Empress::init(ai.clone());
    if let Err(e) = empress.update().await {
        println!("Error: {}", e);
    }
    Ok(ai)
}

async fn parse_response(response: &str) -> Result<(i32, i32, i32), io::Error> {
    let mut lines = response.split('\n');

    let client_number = lines
        .next()
        .ok_or_else(|| Error::new(ErrorKind::InvalidData, "Invalid response."))?
        .parse::<i32>()
        .map_err(|_| Error::new(ErrorKind::InvalidData, "Invalid client number."))?;

    let line = lines
        .next()
        .ok_or_else(|| Error::new(ErrorKind::InvalidData, "Invalid response."))?;

    let mut words = line.split_whitespace();
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
    p_id: usize,
) -> io::Result<AI> {
    parse_response(response)
        .await
        .map(|(client_number, x, y)| {
            info!("Client number detected as [{}].", client_number);
            info!("Map size: ({}, {}).", x, y);
            let ai = AI::new(team, client_number, p_id, client.clone(), (x, y), 1);
            println!("AI #{} > {}", p_id, ai);
            info!("{} initialized.", ai);
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
    p_id: usize,
) -> io::Result<AI> {
    info!("Initializing AI...");
    let ai = checkout_ai_info(client, response, team, p_id).await?;
    kickstart(ai).await
    // info!("Connection ID #{} creates <role?>...", id);
    // handle all types of creation of ia based on id now...
}

async fn start_ai(client: Arc<Mutex<TcpClient>>, team: String, p_id: usize) -> io::Result<AI> {
    info!("Starting AI process n{}...", p_id);
    {
        let mut client_lock = client.lock().await;
        client_lock.send_request(team.clone() + "\n").await?;
    }
    if let Some(response) = {
        let mut client_lock = client.lock().await;
        client_lock.get_response().await
    } {
        match response.trim_end() {
            "ko" => {
                print!("server> {}", response);
                debug!("Server doesn't handle any more connection");
                Err(Error::new(
                    ErrorKind::ConnectionRefused,
                    "No room for player.",
                ))
            }
            _ => {
                info!("Connection to team successful.");
                let ai = init_ai(client.clone(), &response, team, p_id).await?;
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

// indiv testing
// pub async fn launch(address: String, team: String) -> io::Result<AI> {
//     let ai = match tcp::handle_tcp(address.clone()).await {
//         Ok(client) => {
//             info!("Client connected successfully.");
//             let client = Arc::new(Mutex::new(client));
//             match start_ai(client.clone(), team.clone()).await {
//                 Ok(ai) => {
//                     println!("ok");
//                     ai
//                 }
//                 Err(e) => {
//                     eprintln!("Launch Error {}", e);
//                     return Err(Error::new(e.kind(), e));
//                 }
//             }
//         }
//         Err(e) => {
//             return Err(Error::new(e.kind(), e));
//         }
//     };
//     Ok(ai)
// }

// multi-connect
pub async fn launch(address: String, team: String) -> io::Result<()> {
    let mut handles = vec![];
    let team = Arc::new(team);
    let connection_id = Arc::new(AtomicUsize::new(0));
    let stop_flag = Arc::new(AtomicBool::new(false));

    loop {
        if stop_flag.load(Ordering::SeqCst) {
            println!("Stop flag is set, breaking the loop.");
            break;
        }

        match tcp::handle_tcp(address.clone()).await {
            Ok(client) => {
                let team = Arc::clone(&team);
                let client = Arc::new(Mutex::new(client));
                let id = connection_id.fetch_add(1, Ordering::SeqCst);
                let stop_flag = Arc::clone(&stop_flag);

                let handle = task::spawn(async move {
                    let result = start_ai(client.clone(), team.to_string(), id).await;

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
        debug!("Connection refused, handles is empty.");
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
