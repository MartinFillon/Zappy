//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// knight
//

use crate::{
    ai::{fetus::Fetus, start_ai, AIHandler, Incantationers, AI},
    commands::{drop_object, fork, incantation, inventory, look_around, take_object},
    move_towards_broadcast::{backtrack_eject, move_towards_broadcast},
    tcp::{
        command_handle::{CommandError, CommandHandler, DirectionMessage, ResponseResult},
        handle_tcp, TcpClient,
    },
};

use core::fmt;
use std::fmt::{Display, Formatter};
use std::io::{self, Error};
use std::sync::Arc;

use async_trait::async_trait;
use tokio::{sync::Mutex, task};

use log::{debug, error, info};
use zappy_macros::Bean;

use super::Listeners;

#[derive(Debug, Clone, Bean)]
pub struct Knight {
    info: AI,
}

#[async_trait]
impl AIHandler for Knight {
    fn init(info: AI) -> Self {
        println!("Knight has been created.");
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        loop {
            info!("Handling knight [Queen {}]...", self.info().p_id);
            self.handle_message().await?;

            if self.info().level == 6 && (self.info().p_id == 3 || self.info().p_id == 4) {
                break;
            }
            if self.can_incantate().await? {
                let mut level = self.info().level;
                {
                    let mut client = self.info().client().lock().await;
                    let res = incantation::incantation(&mut client).await;
                    if let ResponseResult::Incantation(lvl) =
                        Knight::knight_checkout_response(&mut client, res).await?
                    {
                        level = lvl;
                    }
                }
                self.info.set_level(level);
                continue;
            }
            if self.check_food().await? < 8 {
                info!(
                    "Knight [Queen {}]: not enough food, producing more...",
                    self.info().p_id
                );
                {
                    let mut client = self.info().client().lock().await;
                    let res = fork::fork(&mut client).await;
                    if let ResponseResult::OK =
                        Knight::knight_checkout_response(&mut client, res).await?
                    {
                        let info = self.info.clone();
                        tokio::spawn(async move {
                            let _ = Fetus::fork_dupe(info, None).await;
                        });
                    }
                };
                while self.check_food().await? < 10 {
                    self.handle_message().await?;
                    let mut client = self.info().client().lock().await;
                    let res = take_object::take_object(&mut client, "food").await;
                    Knight::knight_checkout_response(&mut client, res).await?;
                }
            }
        }
        Err(CommandError::DeadReceived)
    }

    async fn fork_dupe(info: AI, set_id: Option<usize>) -> io::Result<()> {
        let client = match handle_tcp(info.address.clone(), info.team.clone()).await {
            Ok(client) => {
                debug!("New `Knight` client connected successfully.");
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
                    let mut knight = Knight::init(ai.clone());
                    if let Err(e) = knight.update().await {
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
}

#[async_trait]
impl Incantationers for Knight {
    async fn handle_eject(
        client: &mut TcpClient,
        res: Result<ResponseResult, CommandError>,
    ) -> Result<ResponseResult, CommandError> {
        if let Ok(ResponseResult::Eject(ref dir)) = res {
            if backtrack_eject(client, dir.clone()).await {
                let response = client.check_response().await?;
                client.handle_response(response).await?;
            }
        }
        res
    }

    async fn handle_elevating(
        client: &mut TcpClient,
        mut res: Result<ResponseResult, CommandError>,
    ) -> Result<ResponseResult, CommandError> {
        if let Ok(ResponseResult::Elevating) = res {
            res = Ok(incantation::handle_incantation(client).await?);
            if let Some(response) = client.get_response().await {
                return client.handle_response(response).await;
            }
        }
        res
    }
}

#[async_trait]
impl Listeners for Knight {
    async fn handle_message(&mut self) -> Result<ResponseResult, CommandError> {
        let mut id: usize = 0;
        self.analyse_messages(&mut id).await?;
        if id != 0 {
            self.info.set_p_id(id);
        }
        Ok(ResponseResult::OK)
    }
}

impl Knight {
    fn new(info: AI) -> Self {
        Self { info }
    }

    async fn die(&mut self, id: usize) {
        let mut client_lock = self.info.client.lock().await;
        let mut total = 0;

        println!("Knight #{} is killing himself.", id);
        loop {
            let command = drop_object::drop_object(&mut client_lock, "food").await;
            if let Ok(ResponseResult::OK) = command {
                info!("Knight #{} dropping food x1...", id);
                total += 1;
            }
            if command.is_err() {
                info!("Fetus dropped x{} food", total);
                info!("Knight #{} died.", id);
                break;
            }
        }
    }

    async fn check_food(&mut self) -> Result<usize, CommandError> {
        let mut client = self.info().client().lock().await;
        let res = inventory::inventory(&mut client).await;
        if let ResponseResult::Inventory(inv) =
            Knight::knight_checkout_response(&mut client, res).await?
        {
            return Ok(inv[0].1 as usize);
        }
        Err(CommandError::InvalidResponse)
    }

    async fn analyse_messages(&mut self, p_id: &mut usize) -> Result<ResponseResult, CommandError> {
        let mut client = self.info().client().lock().await;
        while let Some(message) = client.pop_message() {
            info!(
                "Knight [Queen {}]: handling message: {}",
                self.info().p_id,
                message.1
            );
            match message {
                (DirectionMessage::Center, msg) => {
                    if let Ok(id) = msg.parse::<usize>() {
                        p_id.clone_from(&id);
                    }
                }
                (dir, msg) => {
                    if !msg.contains(' ') || msg.len() < 2 {
                        continue;
                    }
                    if let Some(idex) = msg.trim_end_matches('\n').find(' ') {
                        let content = msg.split_at(idex);
                        if let Ok(id) = content.0.parse::<usize>() {
                            if id == self.info().p_id && content.1 == "mv" {
                                let res = move_towards_broadcast(&mut client, dir).await;
                                Knight::knight_checkout_response(&mut client, res).await?;
                            }
                        }
                    }
                }
            }
        }
        Ok(ResponseResult::OK)
    }

    async fn can_incantate(&mut self) -> Result<bool, CommandError> {
        if self.info().level != 1 || self.check_food().await? < 4 {
            return Ok(false);
        }
        let mut client = self.info().client().lock().await;
        let res = look_around::look_around(&mut client).await;
        if let ResponseResult::Tiles(tiles) =
            Knight::knight_checkout_response(&mut client, res).await?
        {
            if !tiles[0].iter().any(|tile| tile.as_str() == "linemate") {
                return Ok(false);
            }
        }
        Ok(true)
    }

    async fn knight_checkout_response(
        client: &mut TcpClient,
        res: Result<ResponseResult, CommandError>,
    ) -> Result<ResponseResult, CommandError> {
        match res {
            Ok(ResponseResult::Eject(_)) => Knight::handle_eject(client, res).await,
            Ok(ResponseResult::Elevating) => Knight::handle_elevating(client, res).await,
            _ => res,
        }
    }
}

impl Display for Knight {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "Knight => {}", self.info)
    }
}
