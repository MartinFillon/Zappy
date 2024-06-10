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
use std::sync::Arc;

use async_trait::async_trait;
use tokio::{sync::Mutex, task};

use log::{debug, info};

#[derive(Debug, Clone)]
pub struct AI {
    team: String,
    cli_id: i32,
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

impl AI {
    fn new(
        team: String,
        cli_id: i32,
        client: Arc<Mutex<TcpClient>>,
        map: (i32, i32),
        level: usize,
    ) -> Self {
        Self {
            team,
            cli_id,
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
            "AI = [team: {}, client: {}, map: ({}, {}), level: {}]",
            self.team, self.cli_id, self.map.0, self.map.1, self.level
        )
    }
}

// test here
#[allow(dead_code)]
async fn kickstart(ai: AI) -> io::Result<()> {
    info!("Sending startup commands...");

    let mut fetus = fetus::Fetus::init(ai.clone());
    if let Err(e) = fetus.update().await {
        println!("Error: {}", e);
    }
    Ok(())
}

async fn init_ai(client: Arc<Mutex<TcpClient>>, response: &str, team: String) -> io::Result<AI> {
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

    let mut ai = match lines.next() {
        Some(line) => {
            let mut words = line.split_whitespace();
            let x = match words.next().and_then(|word| word.parse::<i32>().ok()) {
                Some(val) => val,
                None => {
                    debug!("Failed to parse x coordinate from line: {}", line);
                    return Err(Error::new(ErrorKind::InvalidData, "Invalid x coordinate."));
                }
            };
            let y = match words.next().and_then(|word| word.parse::<i32>().ok()) {
                Some(val) => val,
                None => {
                    debug!("Failed to parse y coordinate from line: {}", line);
                    return Err(Error::new(ErrorKind::InvalidData, "Invalid y coordinate."));
                }
            };
            info!("Map size: ({}, {}).", x, y);
            let ai: AI = AI::new(team, client_number, client.clone(), (x, y), 1);
            println!("AI #{} > {}", client_number, ai);
            info!("{} initialized.", ai);
            // kickstart(ai.clone()).await?; handle ur ai here to test bruh no from main
            ai
        }
        None => return Err(Error::new(ErrorKind::InvalidData, "Invalid response.")),
    };

    Ok(ai)
}

async fn start_ai(client: Arc<Mutex<TcpClient>>, team: String) -> io::Result<AI> {
    info!("Starting AI...");
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
                Err(Error::new(
                    ErrorKind::ConnectionRefused,
                    "No room for player.",
                ))
            }
            _ => {
                info!("Connection to team successful");
                let ai = init_ai(client.clone(), &response, team).await?;
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

//temp to test single program
pub async fn launch(address: String, team: String) -> io::Result<AI> {
    let ai = match tcp::handle_tcp(address.clone()).await {
        Ok(client) => {
            info!("Client connected successfully.");
            let client = Arc::new(Mutex::new(client));
            match start_ai(client.clone(), team.clone()).await {
                Ok(ai) => {
                    println!("ok");
                    ai
                }
                Err(e) => {
                    eprintln!("Launch Error {}", e);
                    return Err(Error::new(e.kind(), e));
                }
            }
        }
        Err(e) => {
            return Err(Error::new(e.kind(), e));
        }
    };
    Ok(ai)
}

// multi-connect
// pub async fn launch(address: String, team: String) -> io::Result<()> {
//     let mut handles = vec![];

//     let team = Arc::new(team);
//     loop {
//         match tcp::handle_tcp(address.clone()).await {
//             Ok(client) => {
//                 let team: Arc<String> = Arc::clone(&team);
//                 let client = Arc::new(Mutex::new(client));
//                 let handle = task::spawn(async move {
//                     let team_str = &*team;
//                     match start_ai(client.clone(), team_str.clone()).await {
//                         Ok(_) => {
//                             println!("ok");
//                             Ok(())
//                         }
//                         Err(e) => {
//                             println!("ko");
//                             Err(e)
//                         }
//                     }
//                 });
//                 handles.push(handle);
//             }
//             Err(e) => {
//                 println!("Failed to handle TCP: {}", e);
//                 break;
//             }
//         }
//     }

//     if handles.is_empty() {
//         debug!("Connection refused, handles is empty.");
//         return Err(Error::new(
//             ErrorKind::ConnectionRefused,
//             "Couldn't reach host.",
//         ));
//     }

//     Ok(())
// }
