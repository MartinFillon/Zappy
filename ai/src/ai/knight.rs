//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// knight
//

use crate::{
    ai::{fork_ai, AIHandler, Incantationers, Listeners, AI},
    commands::{
        broadcast::broadcast,
        fork::fork,
        incantation::{self, handle_incantation},
        inventory::inventory,
        look_around::look_around,
        take_object::take_object,
    },
    move_towards_broadcast::{backtrack_eject, move_towards_broadcast},
    tcp::{
        command_handle::{CommandError, CommandHandler, DirectionMessage, ResponseResult},
        TcpClient,
    },
};

use core::fmt;
use std::fmt::{Display, Formatter};
use std::sync::Arc;

use async_trait::async_trait;
use tokio::sync::Mutex;

#[allow(unused_imports)]
use log::{debug, error, info, warn};
use zappy_macros::Bean;

const FETUS_NEED: usize = 2;
const MIN_FOOD_ON_FLOOR: usize = 200;

#[derive(Debug, Clone, Bean)]
pub struct Knight {
    info: AI,
    level_ref: Arc<Mutex<usize>>,
}

#[async_trait]
impl AIHandler for Knight {
    ///
    /// Initializes the [`Knight`]
    ///
    /// * `info` - `AI` structure that represents the basic info of an AI client
    ///
    fn init(info: AI) -> Self {
        println!("-[{}] Knight has been created.", info.cli_id);
        Self::new(info, Arc::new(Mutex::new(1)))
    }

    ///
    /// [`Knight`]'s main loop
    ///
    async fn update(&mut self) -> Result<(), CommandError> {
        info!(
            "-[{}] Knight [Queen {}] is being handled...",
            self.info().cli_id,
            self.info().p_id
        );
        loop {
            {
                let level = self.level_ref.lock().await;
                if *level != self.info().level {
                    self.info.set_level(*level);
                }
            }
            self.handle_message().await?;
            let mut client = self.info().client().lock().await;
            self.check_enough_food(&mut client, 20).await?;
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
                let response = client
                    .check_response()
                    .await
                    .ok_or(CommandError::NoResponseReceived)?;
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
            res = handle_incantation(client).await;
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
    ///
    /// [`Knight`] initialize the struct with `AI` struct
    ///
    fn new(info: AI, level_ref: Arc<Mutex<usize>>) -> Self {
        Self { info, level_ref }
    }

    ///
    /// [`Knight`] Spawns a new [`Fetus`] if there is not enough food on the floor
    ///
    async fn check_food(&self, client: &mut TcpClient, min: usize) -> Result<(), CommandError> {
        let res = look_around(client).await?;
        if let ResponseResult::Tiles(tiles) = self.knight_checkout_response(client, Ok(res)).await?
        {
            if !tiles.is_empty()
                && tiles[0]
                    .iter()
                    .filter(|item| item.as_str() == "food")
                    .count()
                    < min
            {
                info!(
                    "-[{}] Knight [Queen {}]: not enough food, producing more...",
                    self.info().cli_id,
                    self.info().p_id
                );
                for _ in 0..FETUS_NEED {
                    let res = fork(client).await?;
                    if let ResponseResult::OK =
                        self.knight_checkout_response(client, Ok(res)).await?
                    {
                        let info = self.info.clone();
                        tokio::spawn(async move {
                            if let Err(err) = fork_ai(info.clone()).await {
                                error!("-[{}] AI fork error: {}", info.cli_id, err);
                            } else {
                                println!("-[{}] AI successfully forked.", info.cli_id);
                            }
                        });
                        broadcast(
                            client,
                            format!("{} assign Fetus {}", self.info().cli_id, self.info().p_id)
                                .as_str(),
                        )
                        .await?;
                    }
                }
            }
        }
        Ok(())
    }

    ///
    /// [`Knight`] checks if there is enough food on the floor
    ///
    async fn check_enough_food(
        &self,
        client: &mut TcpClient,
        min: usize,
    ) -> Result<(), CommandError> {
        self.check_food(client, MIN_FOOD_ON_FLOOR).await?;
        let mut res = inventory(client).await?;
        if let ResponseResult::Inventory(mut inv) =
            self.knight_checkout_response(client, Ok(res)).await?
        {
            if !inv.is_empty() && inv[0].0 == "food" {
                res = ResponseResult::OK;
                while inv[0].1 < min as i32 && res == ResponseResult::OK {
                    res = take_object(client, "food").await?;
                    res = Knight::handle_eject(client, Ok(res)).await?;
                    inv[0].1 += 1;
                }
            }
        }
        Ok(())
    }

    ///
    /// [`Knight`] handles the messages received from the server
    ///
    async fn analyse_messages(&mut self) -> Result<ResponseResult, CommandError> {
        let mut client = self.info().client().lock().await;

        while let Some(message) = client.pop_message() {
            debug!(
                "-[{}] Knight [Queen {}]: handling message: {}",
                self.info().cli_id,
                self.info().p_id,
                message.1
            );
            let (dir, msg) = message;
            if !msg.contains(' ') || msg.len() < 2 {
                continue;
            }
            if let Some(idex) = msg.trim_end_matches('\n').find(' ') {
                let content = msg.split_at(idex);
                if let Ok(id) = content.0.parse::<usize>() {
                    if id == self.info().p_id && content.1.trim_start() == "mv" {
                        info!(
                            "-[{}] Knight {} moving towards Queen...",
                            self.info.cli_id, self.info.p_id
                        );
                        let res = move_towards_broadcast(&mut client, dir.clone()).await?;
                        self.knight_checkout_response(&mut client, Ok(res)).await?;
                    }
                    if id == self.info().p_id
                        && content.1.trim_start() == "inc"
                        && self.info().level != 1
                        && dir.clone() == DirectionMessage::Center
                    {
                        debug!(
                            "Knight {} received \"inc\" from Queen, waiting for response...",
                            self.info.p_id
                        );
                        let res = incantation::wait_for_incantation(&mut client).await;
                        if let Err(err) = res {
                            error!(
                                "-[{}] Knight [Queen {}]: incantation error: {}",
                                self.info().cli_id,
                                self.info.p_id,
                                err
                            );
                            return Err(err);
                        }
                        debug!(
                            "[{}] Knight {} received \"inc\" from Queen, read response: {:?}",
                            self.info.cli_id, self.info.p_id, res
                        );
                        self.knight_checkout_response(&mut client, res).await?;
                    }
                }
            }
        }
        Ok(ResponseResult::OK)
    }

    ///
    /// [`Knight`] checks the response from the server to sort
    ///
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

#[cfg(test)]
mod knight_test {
    use super::*;
    use std::sync::Arc;
    use tokio::sync::Mutex;

    fn setup_client() -> TcpClient {
        TcpClient::new("127.0.0.1", "Team".to_string(), 1)
    }

    fn setup_knight() -> Knight {
        let client = setup_client();
        let ai = AI {
            address: "127.0.0.1".to_string(),
            team: "Team".to_string(),
            cli_id: 1,
            p_id: 1,
            client: Arc::new(Mutex::new(client)),
            map: (10, 10),
            level: 1,
            slots: 0,
        };
        Knight::new(ai, Arc::new(Mutex::new(1)))
    }

    #[tokio::test]
    async fn test_knight_init() {
        let knight = setup_knight();

        assert_eq!(knight.info().cli_id, 1);
        assert_eq!(knight.info().p_id, 1);
        assert_eq!(knight.info().level, 1);
    }
}
