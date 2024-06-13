//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// knight
//

#![allow(unused_imports)]

use crate::{
    ai::{AIHandler, Incantationers, AI},
    commands,
    commands::{inventory, take_object},
    move_towards_broadcast::{backtrack_eject, move_towards_broadcast},
    tcp::{
        command_handle::{
            CommandError, CommandHandler, DirectionEject, DirectionMessage, ResponseResult,
        },
        TcpClient,
    },
};

use core::fmt;
use std::fmt::{Display, Formatter};

use async_trait::async_trait;

use log::info;
use zappy_macros::Bean;

use super::Listeners;

#[derive(Debug, Clone, Bean)]
pub struct Knight {
    info: AI,
}

#[async_trait]
impl AIHandler for Knight {
    fn init(info: AI) -> Self {
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        loop {
            info!("Handling knight [Queen {}]...", self.info().p_id);
            self.handle_message().await?;

            if self.info().level == 6 && (self.info().p_id == 7 || self.info().p_id == 8) {
                break; // die or return Err(CommandError::DeadReceived) ??
            }
            if self.check_food().await? < 8 {
                info!(
                    "Knight [Queen {}]: not enough food, producing more...",
                    self.info().p_id
                );
                // create fetus
                while self.check_food().await? < 10 {
                    self.handle_message().await?;
                    let mut client = self.info().client().lock().await;
                    let res = take_object::take_object(&mut client, "food").await;
                    Knight::handle_eject(&mut client, res).await?;
                }
            }
        }

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

    // if needed sinon jenleve
    async fn die(&mut self, id: usize) {
        let mut client_lock = self.info.client.lock().await;
        let mut total = 0;

        println!("Knight #{} is killing himself.", id);
        loop {
            let command = commands::drop_object::drop_object(&mut client_lock, "food").await;
            if let Ok(ResponseResult::OK) = command {
                info!("Knight #{} dropping food x1...", self.info.p_id);
                total += 1;
            }
            if command.is_err() {
                info!("Fetus dropped x{} food", total);
                info!("Knight #{} died.", self.info.p_id);
                break;
            }
        }
    }

    async fn check_food(&mut self) -> Result<usize, CommandError> {
        let mut client = self.info().client().lock().await;
        let res = inventory::inventory(&mut client).await;
        if let ResponseResult::Inventory(inv) = Knight::handle_eject(&mut client, res).await? {
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
                        p_id.clone_from(&(id + 4));
                    }
                }
                (dir, msg) => {
                    if !msg.contains(' ') || msg.len() < 2 {
                        continue;
                    }
                    if let Some(idex) = msg.trim_end_matches('\n').find(' ') {
                        let content = msg.split_at(idex);
                        if let Ok(id) = content.0.parse::<usize>() {
                            if id == *self.info().p_id() && content.1 == "mv" {
                                let res = move_towards_broadcast(&mut client, dir).await;
                                Knight::handle_eject(&mut client, res).await?;
                            }
                        }
                    }
                }
            }
        }
        Ok(ResponseResult::OK)
    }
}

impl Display for Knight {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "Knight => {}", self.info)
    }
}
