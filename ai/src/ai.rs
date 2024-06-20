//
// EPITECH PROJECT, 2024
// ai.rs
// File description:
// zappy ai main functions
//

#![allow(dead_code)]

pub mod bot;
pub mod fetus;
pub mod knight;
pub mod npc;
pub mod queen;

use crate::{
    commands::broadcast,
    tcp::{
        command_handle::{CommandError, CommandHandler, DirectionMessage, ResponseResult},
        handle_tcp, TcpClient,
    },
};

use std::fmt::{self, Display, Formatter};
use std::io::{self, Error, ErrorKind};
use std::sync::{
    atomic::{AtomicBool, AtomicUsize, Ordering},
    Arc,
};

use async_trait::async_trait;
use bot::Bot;
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
    slots: i32,
}

#[derive(Debug, Clone)]
enum Roles {
    Fetus,
    Bot,
    Knight,
    Queen,
}

impl TryFrom<String> for Roles {
    type Error = String;

    fn try_from(value: String) -> Result<Self, Self::Error> {
        match value.as_str() {
            "Fetus" => Ok(Self::Fetus),
            "Bot" => Ok(Self::Bot),
            "Knight" => Ok(Self::Knight),
            "Queen" => Ok(Self::Queen),
            _ => Err(format!("Unknown role: {}", value)),
        }
    }
}

impl Display for Roles {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        match *self {
            Self::Fetus => write!(f, "Fetus"),
            Self::Bot => write!(f, "Bot"),
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
        Roles::Fetus => Box::new(Fetus::init(info.clone())),
        Roles::Bot => Box::new(Bot::init(info.clone())),
        Roles::Knight => Box::new(Knight::init(info.clone())),
        Roles::Queen => Box::new(Queen::init(info.clone())),
    })
}

pub async fn fork_ai(info: AI) -> io::Result<()> {
    let client = match handle_tcp(info.address.clone(), info.team.clone(), info.cli_id).await {
        Ok(client) => {
            info!(
                "[{}] New client connected successfully for FORK.",
                info.cli_id
            );
            Arc::new(Mutex::new(client))
        }
        Err(e) => {
            error!("[{}] New client error from: {}", info.cli_id, e);
            return Err(Error::new(e.kind(), e));
        }
    };
    let team = info.team.clone();
    let address = info.address.clone();

    match start_ai(client, team, address, (info.cli_id, 0), false).await {
        Ok(mut ai) => {
            if let Some((c_id, role, p_id)) = ai.clone().wait_assignment().await {
                ai.set_p_id(p_id);
                ai.set_cli_id(c_id + 1);
                info!(
                    "[{}] Handling assignment of role {} with id {}",
                    info.cli_id, role, p_id
                );
                let mut rle = init_from_broadcast(&ai, role)
                    .map_err(|e| std::io::Error::new(ErrorKind::NotFound, e))?;
                if let Err(e) = rle.update().await {
                    println!("[{}] Error: {}", info.cli_id, e);
                }
                return Ok(());
            }
            warn!(
                "[{}] No role assignment detected, turning to NPC...",
                info.cli_id
            );
        }
        Err(e) => error!("[{}] {}", info.cli_id, e),
    }
    Ok(())
}

#[async_trait]
pub trait AIHandler: Send {
    fn init(info: AI) -> Self
    where
        Self: Sized;
    async fn update(&mut self) -> Result<(), CommandError>;
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
        (cli_id, p_id): (usize, usize),
        client: Arc<Mutex<TcpClient>>,
        map: (i32, i32),
        level: usize,
        slots: i32,
    ) -> Self {
        Self {
            team,
            address,
            cli_id,
            p_id,
            client,
            map,
            level,
            slots,
        }
    }

    async fn wait_assignment(&mut self) -> Option<(usize, String, usize)> {
        let mut client = self.client().lock().await;
        if let Ok(ResponseResult::Message(msg)) = client.get_broadcast().await {
            client.push_message(msg);
        }
        while let Some((dir, msg)) = client.pop_message() {
            info!(
                "[{}] AI {}: handling message: {}",
                self.cli_id, self.p_id, msg
            );
            if dir != DirectionMessage::Center {
                warn!("[{}] Ignoring message, out of bound.", self.cli_id);
                return None;
            }
            let content = if let Some(idex) = msg.trim_end_matches('\n').find(' ') {
                msg.split_at(idex)
            } else {
                ("0", msg.trim_end_matches('\n'))
            };
            if let Ok(c_id) = content.0.parse::<usize>() {
                return self.handle_assign_msg(c_id, content.1).await;
            }
        }
        None
    }

    async fn handle_assign_msg(&self, c_id: usize, msg: &str) -> Option<(usize, String, usize)> {
        if msg.starts_with(" assign ") {
            let mut lines = msg.split_whitespace();
            lines.next();

            let role: &str = lines.next()?;
            let p_id = lines.next().and_then(|word| word.parse::<usize>().ok())?;

            info!(
                "[{}] AI is being assigned {} with id {}...",
                self.cli_id, role, p_id
            );
            return Some((c_id, role.to_string(), p_id));
        }
        None
    }
}

impl Display for AI {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(
            f,
            "AI #{} = [team: {}, player ID: {}, map: ({}, {}), level: {}, leftover slots: {}]",
            self.cli_id, self.team, self.p_id, self.map.0, self.map.1, self.level, self.slots
        )
    }
}

async fn parse_response(
    response: &str,
    client: Arc<Mutex<TcpClient>>,
) -> Result<(i32, i32, i32), io::Error> {
    let mut cli: tokio::sync::MutexGuard<TcpClient> = client.lock().await;
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
            info!("[{}] x{} unused slot(s)/ egg(s).", c_id, client_number);
            info!("[{}] Map size: {}x{}.", c_id, x, y);
            let ai = AI::new(
                team,
                address,
                (c_id, p_id),
                client.clone(),
                (x, y),
                1,
                client_number,
            );
            println!("[{}] New! >> {}", c_id, ai);
            debug!("[{}] AI is initialized.", ai.cli_id);
            ai
        })
        .map_err(|e: Error| {
            warn!("[{}] Failed to parse response: {}", c_id, e);
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
    info!("[{}] Initializing AI...", c_id);

    let ai = checkout_ai_info(client, response, team, address, (c_id, p_id)).await?;
    match ai.cli_id {
        0..=3 => {
            let mut queen = queen::Queen::init(ai.clone());
            if let Err(e) = queen.update().await {
                error!("[{}] Error: {}", queen.info().cli_id, e);
            }
        }
        _ => {
            let mut bot = bot::Bot::init(ai.clone());
            if let Err(e) = bot.update().await {
                error!("[{}] Error: {}", bot.info().cli_id, e);
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
    println!("[{}] Starting AI process...", c_id);
    {
        let client_lock = client.lock().await;
        client_lock.send_request(team.clone() + "\n").await?;
    }
    if let Some(response) = {
        let mut client_lock = client.lock().await;
        client_lock.get_response().await
    } {
        println!("[{}] server> {}", c_id, response);
        match response.trim_end() {
            "ko" => {
                debug!("[{}] Server doesn't handle any more connection.", c_id);
                Err(Error::new(
                    ErrorKind::ConnectionRefused,
                    "No room for player.",
                ))
            }
            _ => {
                info!("[{}] Connection to team successful.", c_id);
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
        debug!("[{}] Host not reachable.", c_id);
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
            println!(
                "[AT {:?}] Stop flag is set, breaking the loop.",
                connection_id
            );
            break;
        }

        let team = Arc::clone(&team);
        let address = Arc::clone(&address);
        let connection_id = Arc::clone(&connection_id);
        let stop_flag = Arc::clone(&stop_flag);

        let curr_id = connection_id.load(Ordering::SeqCst);
        println!("[{}] Attempting connection...", curr_id);

        match handle_tcp(address.to_string(), team.to_string(), curr_id).await {
            Ok(client) => {
                let client = Arc::new(Mutex::new(client));
                let id = connection_id.fetch_add(1, Ordering::SeqCst);

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
                            println!("[{}] Connection handled successfully", id);
                            Ok(())
                        }
                        Err(e) => {
                            println!("[{}] Connection failed: {}", id, e);
                            stop_flag.store(true, Ordering::SeqCst);
                            Err(e)
                        }
                    }
                });
                handles.push(handle);
            }
            Err(e) => {
                println!("[{}] Failed to handle TCP: {}", curr_id, e);
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

    for (id, handle) in handles.into_iter().enumerate() {
        if let Err(e) = handle.await {
            println!("[{}] Task failed: {:?}", id, e);
        }
    }

    Ok(())
}
