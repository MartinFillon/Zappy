//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// knight
//

use crate::{
    ai::{fork_ai, AIHandler, Incantationers, AI},
    commands::{broadcast, drop_object, fork, incantation, inventory, look_around, take_object},
    move_towards_broadcast::{backtrack_eject, move_towards_broadcast},
    tcp::{
        command_handle::{CommandError, CommandHandler, ResponseResult},
        TcpClient,
    },
};

use core::fmt;
use std::fmt::{Display, Formatter};
use std::sync::Arc;

use async_trait::async_trait;
use tokio::sync::Mutex;

use log::{error, info};
use zappy_macros::Bean;

use super::Listeners;

#[derive(Debug, Clone, Bean)]
pub struct Knight {
    info: AI,
    level_ref: Arc<Mutex<usize>>,
}

const MIN_FOOD_ON_FLOOR: usize = 200;

#[async_trait]
impl AIHandler for Knight {
    fn init(info: AI) -> Self {
        println!("[{}] Knight has been created.", info.cli_id);
        Self::new(info, Arc::new(Mutex::new(1)))
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        info!(
            "[{}] Knight [Queen {}] is being handled...",
            self.info().cli_id,
            self.info().p_id
        );
        loop {
            info!("Handling knight [Queen {}]...", self.info().p_id);
            {
                let level = self.level_ref.lock().await;
                if *level != self.info().level {
                    self.info.set_level(*level);
                }
            }
            self.handle_message().await?;

            {
                let mut client = self.info().client().lock().await;
                self.check_enough_food(&mut client, 10).await?;
            }
            if self.can_incantate().await {
                {
                    let mut client = self.info().client().lock().await;
                    println!(
                        "[{}] Knight {} incantating...",
                        self.info.cli_id, self.info.p_id
                    );
                    let res = incantation::incantation(&mut client).await;
                    println!(
                        "[{}] Knight {} incantation result: {:?}",
                        self.info.cli_id, self.info.p_id, res
                    );
                    if let Ok(ResponseResult::Incantation(lvl)) =
                        self.knight_checkout_response(&mut client, res).await
                    {
                        let mut level = self.level_ref.lock().await;
                        *level = lvl;
                        println!(
                            "[{}] Knight {} done. Now level {}",
                            self.info.cli_id, self.info.p_id, *level
                        );
                    }
                }
                continue;
            }
        }
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
                let response = client.check_response().await;
                client.handle_response(response).await?;
            }
        }
        res
    }

    async fn handle_elevating(
        &self,
        client: &mut TcpClient,
        mut res: Result<ResponseResult, CommandError>,
    ) -> Result<ResponseResult, CommandError> {
        if let Ok(ResponseResult::Elevating) = res {
            res = incantation::handle_incantation(client).await;
            if let Ok(ResponseResult::Incantation(lvl)) = res {
                let mut level = self.level_ref.lock().await;
                *level = lvl;
            }
        }
        res
    }
}

#[async_trait]
impl Listeners for Knight {
    async fn handle_message(&mut self) -> Result<ResponseResult, CommandError> {
        self.analyse_messages().await?;
        Ok(ResponseResult::OK)
    }
}

impl Knight {
    fn new(info: AI, level_ref: Arc<Mutex<usize>>) -> Self {
        Self { info, level_ref }
    }

    async fn die(&mut self, id: usize) {
        let mut client_lock = self.info.client.lock().await;
        let mut total = 0;

        loop {
            let command = drop_object::drop_object(&mut client_lock, "food").await;
            if let Ok(ResponseResult::OK) = command {
                total += 1;
            }
            if command.is_err() {
                info!("[{}] Knight dropped x{} food", self.info.cli_id, total);
                info!("[{}] AI : Knight has killed himself.", id);
                break;
            }
        }
    }

    async fn check_food(&self, client: &mut TcpClient, min: usize) -> Result<(), CommandError> {
        let res = look_around::look_around(client).await;
        if let ResponseResult::Tiles(tiles) = self.knight_checkout_response(client, res).await? {
            if !tiles.is_empty()
                && tiles[0]
                    .iter()
                    .filter(|item| item.as_str() == "food")
                    .count()
                    < min
            {
                info!(
                    "Knight [Queen {}]: not enough food, producing more...",
                    self.info().p_id
                );
                let res = fork::fork(client).await?;
                if let ResponseResult::OK = self.knight_checkout_response(client, Ok(res)).await? {
                    let info = self.info.clone();
                    tokio::spawn(async move {
                        if let Err(err) = fork_ai(info.clone()).await {
                            error!("[{}] AI fork error: {}", info.cli_id, err);
                        } else {
                            println!("[{}] AI successfully forked.", info.cli_id);
                        }
                    });
                    broadcast::broadcast(
                        client,
                        format!("{} assign Fetus {}", self.info().cli_id, self.info().p_id)
                            .as_str(),
                    )
                    .await?;
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
        let mut res = inventory::inventory(client).await;
        if let ResponseResult::Inventory(mut inv) =
            self.knight_checkout_response(client, res).await?
        {
            if !inv.is_empty() && inv[0].0 == "food" {
                res = Ok(ResponseResult::OK);
                while inv[0].1 < min as i32 && res == Ok(ResponseResult::OK) {
                    res = take_object::take_object(client, "food").await;
                    res = Knight::handle_eject(client, res).await;
                    inv[0].1 += 1;
                }
            }
        }
        Ok(())
    }

    async fn analyse_messages(&mut self) -> Result<ResponseResult, CommandError> {
        let mut client = self.info().client().lock().await;

        while let Some(message) = client.pop_message() {
            println!(
                "Knight [Queen {}]: handling message: {}",
                self.info().p_id,
                message.1
            );
            self.check_enough_food(&mut client, 10).await?;
            let (dir, msg) = message;
            if !msg.contains(' ') || msg.len() < 2 {
                continue;
            }
            if let Some(idex) = msg.trim_end_matches('\n').find(' ') {
                let content = msg.split_at(idex);
                if let Ok(id) = content.0.parse::<usize>() {
                    if id == self.info().p_id && content.1.trim_start() == "mv" {
                        let res = move_towards_broadcast(&mut client, dir).await;
                        self.knight_checkout_response(&mut client, res).await?;
                    }
                    if id == self.info().p_id
                        && content.1.trim_start() == "inc"
                        && self.info().level != 1
                    {
                        let response = client.check_response().await;
                        let res = client.handle_response(response).await;
                        println!(
                            "Knight {} received \"inc\" from Queen, read response: {:?}",
                            self.info.p_id, res
                        );
                        self.knight_checkout_response(&mut client, res).await?;
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
            self.knight_checkout_response(&mut client, res).await
        {
            if tiles[0].iter().any(|tile| tile.as_str() == "linemate") {
                return true;
            }
        }
        false
    }

    async fn knight_checkout_response(
        &self,
        client: &mut TcpClient,
        res: Result<ResponseResult, CommandError>,
    ) -> Result<ResponseResult, CommandError> {
        match res {
            Ok(ResponseResult::Eject(_)) => Knight::handle_eject(client, res).await,
            Ok(ResponseResult::Elevating) => self.handle_elevating(client, res).await,
            _ => res,
        }
    }
}

impl Display for Knight {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "Knight => {}", self.info)
    }
}
