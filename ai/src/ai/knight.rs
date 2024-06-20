//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// knight
//

use crate::{
    ai::{fetus::Fetus, start_ai, AIHandler, Incantationers, AI},
    commands::{drop_object, fork, incantation, inventory, look_around::{self, look_around}, take_object},
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

static mut LEVEL: usize = 1;
const MIN_FOOD_ON_FLOOR: usize = 300;

#[async_trait]
impl AIHandler for Knight {
    fn init(info: AI) -> Self {
        println!("Knight has been created.");
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        loop {
            info!("Handling knight [Queen {}]...", self.info().p_id);
            if unsafe{LEVEL} != self.info().level {
                self.info.set_level(unsafe{LEVEL});
            }
            let _ = self.handle_message().await;

            if self.info().level == 6 && (self.info().p_id == 3 || self.info().p_id == 4) {
                break;
            }
            {
                let mut client = self.info().client().lock().await;
                let _ = self.check_enough_food(&mut client, 10).await;
            }
            if self.can_incantate().await {
                {
                    let mut client = self.info().client().lock().await;
                    println!("Knight {} incantating...", self.info.p_id);
                    let res = incantation::incantation(&mut client).await;
                    println!("Knight {} incantation result: {:?}", self.info.p_id, res);
                    if let Ok(ResponseResult::Incantation(lvl)) =
                        Knight::knight_checkout_response(&mut client, res).await
                    {
                        unsafe{LEVEL = lvl;}
                        println!("Knight {} done. Now level {}", self.info.p_id, unsafe{LEVEL});
                    }
                }
                continue;
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
            res = incantation::handle_incantation(client).await;
            if let Ok(ResponseResult::Incantation(lvl)) = res {
                unsafe {
                    LEVEL = lvl;
                }
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

    async fn check_food(&self, client: &mut TcpClient, min: usize) -> Result<(), CommandError> {
        let res = look_around::look_around(client).await;
        if let ResponseResult::Tiles(tiles) = Knight::knight_checkout_response(client, res).await? {
            if !tiles.is_empty() && tiles[0].iter().filter(|item| item.as_str() == "food").count() < min {
                info!(
                    "Knight [Queen {}]: not enough food, producing more...",
                    self.info().p_id
                );
                let res = fork::fork(client).await;
                if let Ok(ResponseResult::OK) = Knight::knight_checkout_response(client, res).await
                {
                    let info = self.info.clone();
                    tokio::spawn(async move {
                        let _ = Fetus::fork_dupe(info, None).await;
                    });
                }
            }
        }
        Ok(())
    }

    async fn check_enough_food(
        &self,
        client: &mut TcpClient,
        min: usize,
    ) -> Result<(), CommandError> {
        self.check_food(client, MIN_FOOD_ON_FLOOR).await?;
        let res = inventory::inventory(client).await;
        if let ResponseResult::Inventory(mut inv) = Knight::knight_checkout_response(client, res).await? {
            if !inv.is_empty() && inv[0].0 == "food" {
                while inv[0].1 < min as i32 {
                    let mut res = take_object::take_object(client, "food").await;
                    res = Knight::handle_eject(client, res).await;
                    if res == Ok(ResponseResult::OK) {
                        inv[0].1 += 1;
                    }
                }
            }
        }
        Ok(())
    }

    async fn analyse_messages(&mut self, p_id: &mut usize) -> Result<ResponseResult, CommandError> {
        let mut client = self.info().client().lock().await;
        while let Some(message) = client.pop_message() {
            println!(
                "Knight [Queen {}]: handling message: {}",
                self.info().p_id,
                message.1
            );
            let _ = self.check_enough_food(&mut client, 10).await;
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
                            if id == self.info().p_id && content.1.trim_start() == "mv" {
                                let res = move_towards_broadcast(&mut client, dir).await;
                                Knight::knight_checkout_response(&mut client, res).await?;
                            }
                            if id == self.info().p_id && content.1.trim_start() == "inc" && self.info().level != 1 {
                                let response = client.check_response().await?;
                                let res = client.handle_response(response).await;
                                println!("Knight {} received \"inc\" from Queen, read response: {:?}", self.info.p_id, res);
                                Knight::knight_checkout_response(&mut client, res).await?;
                            }
                        }
                    }
                }
            }
        }
        Ok(ResponseResult::OK)
    }

    async fn can_incantate(&mut self) -> bool {
        if self.info().level != 1 {
            return false;
        }
        let mut client = self.info().client().lock().await;
        let res = look_around::look_around(&mut client).await;
        println!("Knight {} Look returned: {:?}", self.info.p_id, res);
        if let Ok(ResponseResult::Tiles(tiles)) =
            Knight::knight_checkout_response(&mut client, res).await
        {
            if tiles[0].iter().any(|tile| tile.as_str() == "linemate") {
                return true;
            }
        }
        false
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
