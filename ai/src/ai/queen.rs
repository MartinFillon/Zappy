//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// queen
//

use super::Listeners;
use crate::{
    ai::{bot::Bot, knight::Knight, start_ai, AIHandler, Incantationers, AI},
    commands::{self, turn::DirectionTurn},
    elevation::{Config, Inventory},
    move_towards_broadcast::{backtrack_eject, turn_towards_broadcast},
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

use log::{debug, error, info, warn};
use zappy_macros::Bean;

const NB_INIT_BOTS: usize = 2;
const QUEENS_IDS: [usize; 4] = [2, 1, 4, 3];

#[derive(Debug, Clone, Default)]
struct LookInfo {
    nb_player: usize,
    inv: Inventory,
}

#[derive(Debug, Clone, Bean)]
pub struct Queen {
    pub info: AI,
    inv: Inventory,
    look: LookInfo,
    requirement: Config,
    can_move: bool,
    can_start: bool,
}

#[async_trait]
impl Incantationers for Queen {
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
        _client: &mut TcpClient,
        res: Result<ResponseResult, CommandError>,
    ) -> Result<ResponseResult, CommandError> {
        res
    }
}

#[async_trait]
impl Listeners for Queen {
    async fn handle_message(&mut self) -> Result<ResponseResult, CommandError> {
        let mut can_move = false;
        let mut can_start = false;
        self.analyse_messages(&mut can_move, &mut can_start).await?;
        if can_move {
            self.set_can_move(true);
        }
        if can_start {
            self.set_can_start(true);
        }
        Ok(ResponseResult::OK)
    }
}

impl Queen {
    /// Creates a new [`Queen`].
    fn new(info: AI) -> Self {
        Self {
            info,
            inv: Default::default(),
            look: Default::default(),
            requirement: zappy_json::create_from_file::<Config>("config.json").unwrap(),
            can_move: false,
            can_start: false,
        }
    }

    /**
        Move [`queen`] at level 4,
        we assume that all the queens have the same direction
    */
    async fn move_queen_first_step(&mut self) -> Result<(), CommandError> {
        self.set_can_move(false);
        if self.info.p_id == 2 | 4 {
            return Ok(());
        }
        let mut cli = self.info.client.lock().await;
        commands::move_up::move_up(&mut cli).await?;
        let broad_res =
            commands::broadcast::broadcast(&mut cli, format!("{} mv", self.info.p_id).as_str())
                .await?;
        Queen::handle_eject(&mut cli, Ok(broad_res)).await?;
        Ok(())
    }

    /**
        Move [`queen`] at level 6,
        we will move queen's direction and then reunite them in a single tile
    */
    async fn move_queen_second_step(&mut self) -> Result<(), CommandError> {
        match self.info.p_id {
            1 | 2 => {
                let mut cli = self.info.client.lock().await;
                commands::move_up::move_up(&mut cli).await?;
                commands::broadcast::broadcast(&mut cli, format!("{} mv", self.info.p_id).as_str())
                    .await?;
            }
            3 | 4 => {
                let mut cli = self.info.client.lock().await;
                commands::turn::turn(&mut cli, DirectionTurn::Left).await?;
                commands::turn::turn(&mut cli, DirectionTurn::Left).await?;
                commands::move_up::move_up(&mut cli).await?;
                commands::broadcast::broadcast(&mut cli, format!("{} mv", self.info.p_id).as_str())
                    .await?;
            }
            _ => (),
        }
        Ok(())
    }

    async fn check_move_elevation(&mut self) -> Result<(), CommandError> {
        if !self.can_move() {
            return Ok(());
        }
        match self.info.level {
            4 => self.move_queen_first_step().await,
            6 => self.move_queen_second_step().await,
            _ => Ok(()),
        }
    }

    async fn incantate(&mut self) -> Result<(), CommandError> {
        let mut level = self.info().level;
        {
            let mut cli = self.info.client.lock().await;
            commands::broadcast::broadcast(&mut cli, format!("{} inc", self.info().p_id).as_str())
                .await?;
            let incant_res = commands::incantation::incantation(&mut cli).await;
            if let ResponseResult::Incantation(lvl) =
                Queen::handle_eject(&mut cli, incant_res).await?
            {
                level = lvl;
            }
        };
        self.info.set_level(level);
        Ok(())
    }

    async fn check_enough_food(&mut self, min: usize) -> Result<(), CommandError> {
        if *self.inv.food() >= min || *self.look.inv.food() == 0 {
            return Ok(());
        }
        let mut cli = self.info.client.lock().await;
        if let Ok(ResponseResult::OK) = commands::take_object::take_object(&mut cli, "food").await {
            self.inv.set_food(self.inv.food() + 1);
        }
        Ok(())
    }

    async fn fork_servant(&mut self) -> Result<(), CommandError> {
        let mut cli = self.info.client.lock().await;

        commands::fork::fork(&mut cli).await?;

        let info = self.info.clone();
        tokio::spawn(async move {
            if let Err(err) = Knight::fork_dupe(info.clone(), Some(info.p_id + 4)).await {
                error!("{err}");
            } else {
                println!("Knight with id {} created.", info.p_id + 4)
            }
        });

        commands::broadcast::broadcast(&mut cli, self.info.p_id.to_string().as_str()).await?;
        info!("I as the queen ({}), bestow my life uppon you", 0);

        for _ in 0..NB_INIT_BOTS {
            commands::fork::fork(&mut cli).await?;
            let info = self.info.clone();
            tokio::spawn(async move {
                if let Err(err) = Bot::fork_dupe(info.clone(), Some(info.p_id)).await {
                    error!("{err}");
                } else {
                    println!("Bot with id {} created.", info.p_id);
                }
            });
            commands::broadcast::broadcast(&mut cli, self.info.p_id.to_string().as_str()).await?;
        }

        info!("Miserable peasants... SERVE ME.\n");

        Ok(())
    }

    fn check_requirement(&self) -> bool {
        let idx = self.info.level - 1;
        let require = &self.requirement.elevation[idx];
        let r_inv = require.inv();
        let look = &self.look;

        look.nb_player >= *require.nb_players()
            && look.inv.food() >= r_inv.food()
            && look.inv.linemate() >= r_inv.linemate()
            && look.inv.deraumere() >= r_inv.deraumere()
            && look.inv.sibur() >= r_inv.sibur()
            && look.inv.mendiane() >= r_inv.mendiane()
            && look.inv.phiras() >= r_inv.phiras()
            && look.inv.thystame() >= r_inv.thystame()
    }

    fn convert_to_look_info(&mut self, vec: Vec<String>) {
        self.look.inv.clear();

        let inv: &mut Inventory = &mut self.look.inv;

        for elem in vec.iter() {
            match elem.as_str() {
                "player" => self.look.nb_player += 1,
                "food" => inv.set_food(inv.food() + 1),
                "linemate" => inv.set_linemate(inv.linemate() + 1),
                "deraumere" => inv.set_deraumere(inv.deraumere() + 1),
                "sibur" => inv.set_sibur(inv.sibur() + 1),
                "mendiane" => inv.set_mendiane(inv.mendiane() + 1),
                "phiras" => inv.set_phiras(inv.phiras() + 1),
                "thystame" => inv.set_thystame(inv.thystame() + 1),
                _ => (),
            }
        }
    }

    /// Transform Inventory info to exploit them later.
    fn convert_to_inv(&mut self, vec: Vec<(String, i32)>) {
        for elem in vec.iter() {
            match elem.0.as_str() {
                "food" => self.inv.set_food(elem.1 as usize),
                "linemate" => self.inv.set_linemate(elem.1 as usize),
                "deraumere" => self.inv.set_deraumere(elem.1 as usize),
                "sibur" => self.inv.set_sibur(elem.1 as usize),
                "mendiane" => self.inv.set_mendiane(elem.1 as usize),
                "phiras" => self.inv.set_phiras(elem.1 as usize),
                "thystame" => self.inv.set_thystame(elem.1 as usize),
                _ => (),
            }
        }
    }

    async fn handle_message_content(
        &self,
        client: &mut TcpClient,
        id: usize,
        dir: DirectionMessage,
        msg: &str,
        can_move: &mut bool,
        can_start: &mut bool,
    ) -> Result<ResponseResult, CommandError> {
        if msg.starts_with("lvl ") {
            if let Ok(lvl) = msg.split_at(3).1.parse::<i32>() {
                if (lvl == 4 && id == QUEENS_IDS[self.info().p_id - 1])
                    || (lvl == 6
                        && ((id == 1 | 2 && self.info().cli_id == 3 | 4)
                            || (id == 3 | 4 && self.info().cli_id == 1 | 2)))
                {
                    *can_move = true;
                }
            }
        } else if msg == "Done" {
            turn_towards_broadcast(client, dir).await?;
            *can_start = true;
        }
        Ok(ResponseResult::OK)
    }

    async fn analyse_messages(
        &mut self,
        can_move: &mut bool,
        can_start: &mut bool,
    ) -> Result<ResponseResult, CommandError> {
        let mut client = self.info().client().lock().await;
        while let Some((dir, msg)) = client.pop_message() {
            info!("Queen {}: handling message: {}", self.info().cli_id, msg);
            let content = if let Some(idex) = msg.trim_end_matches('\n').find(' ') {
                msg.split_at(idex)
            } else {
                ("0", msg.trim_end_matches('\n'))
            };
            if let Ok(id) = content.0.parse::<usize>() {
                self.handle_message_content(&mut client, id, dir, content.1, can_move, can_start)
                    .await?;
            }
        }
        Ok(ResponseResult::OK)
    }
}

#[async_trait]
impl AIHandler for Queen {
    fn init(info: AI) -> Self {
        println!("Queen has arrived.");
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        while !self.can_start {
            {
                let mut client = self.info().client().lock().await;
                println!("Queen {}: waiting for \"Done\"...", self.info.p_id);
                if let ResponseResult::Message(msg) = client.get_broadcast().await? {
                    client.push_message(msg);
                }
            }
            self.handle_message().await?;
        }
        println!("Queen {}: received done successfully.", self.info.p_id);
        self.fork_servant().await?;
        loop {
            self.handle_message().await?;
            self.check_move_elevation().await?;

            let look_res = {
                let mut cli = self.info.client.lock().await;
                let res = commands::look_around::look_around(&mut cli).await;
                Queen::handle_eject(&mut cli, res).await
            };
            if let Ok(ResponseResult::Tiles(vec)) = look_res {
                self.convert_to_look_info(vec[0].clone());
            }

            let inventory_res = {
                let mut cli = self.info.client.lock().await;
                let res = commands::inventory::inventory(&mut cli).await;
                Queen::handle_eject(&mut cli, res).await
            };
            if let Ok(ResponseResult::Inventory(vec)) = inventory_res {
                self.convert_to_inv(vec);
            }

            self.check_enough_food(3).await?;

            if self.check_requirement() {
                println!("Ai Queen #{} is incantating", self.info.p_id);
                if let Err(e) = self.incantate().await {
                    warn!("Error from incantation: {}", e);
                    println!("Error with Queen #{} incantating.", self.info.p_id);
                }
            }
        }
    }

    async fn fork_dupe(info: AI, set_id: Option<usize>) -> io::Result<()> {
        let client = match handle_tcp(info.address.clone(), info.team.clone()).await {
            Ok(client) => {
                debug!("New `Queen` client connected successfully.");
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
                    let mut queen = Queen::init(ai.clone());
                    if let Err(e) = queen.update().await {
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

impl Display for Queen {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "Queen => {}", self.info)
    }
}
