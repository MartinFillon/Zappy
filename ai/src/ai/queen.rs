//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// queen
//

use core::fmt;
use std::fmt::{Display, Formatter};

use crate::{
    ai::{AIHandler, AI},
    commands,
    elevation::{Config, Inventory},
    tcp::{
        command_handle::{self, CommandError, ResponseResult},
        TcpClient,
    },
};
use log::info;
use tokio::{sync::Mutex, task};

use async_trait::async_trait;

#[derive(Debug, Clone, Default)]
struct LookInfo {
    nb_player: usize,
    inv: Inventory,
}

#[derive(Debug, Clone)]
pub struct Queen {
    pub info: AI,
    inv: Inventory,
    look: LookInfo,
    requirement: Config,
}

impl Queen {
    /// Creates a new [`Queen`].
    fn new(info: AI) -> Self {
        // Requirement !
        Self {
            info,
            inv: Default::default(),
            look: Default::default(),
            requirement: zappy_json::create_from_file::<Config>("config.json").unwrap(),
        }
    }

    async fn incantate(&mut self) {
        let mut cli = self.info.client.lock().await;
        let _ = commands::broadcast::broadcast(&mut cli, "Incantation !").await;

        let val = commands::incantation::incantation(&mut cli).await;
        match val {
            Ok(ResponseResult::Incantation(lvl)) => {
                self.info.level = lvl;
                println!("{}", self);
            }
            Err(err) => println!("{}", err),
            _ => (),
        }
    }

    async fn check_enough_food(&mut self, min: usize) -> Result<(), command_handle::CommandError> {
        if *self.inv.food() >= min || *self.look.inv.food() == 0 {
            return Ok(());
        }
        let mut cli = self.info.client.lock().await;
        if let Ok(ResponseResult::OK) = commands::take_object::take_object(&mut cli, "food").await {
            self.inv.set_food(self.inv.food() + 1);
        }
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

        let mut inv: &mut Inventory = &mut self.look.inv;

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
}

#[async_trait]
// Handle Eject DON'T FORGET.
impl AIHandler for Queen {
    fn init(info: AI) -> Self {
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), command_handle::CommandError> {
        loop {
            let val = {
                let mut cli = self.info.client.lock().await;
                commands::look_around::look_around(&mut cli).await?
            };
            if let ResponseResult::Tiles(vec) = val {
                self.convert_to_look_info(vec[0].clone());
            }

            let val = {
                let mut cli = self.info.client.lock().await;
                commands::inventory::inventory(&mut cli).await?
            };
            if let ResponseResult::Inventory(vec) = val {
                self.convert_to_inv(vec);
            }

            self.check_enough_food(3).await?;

            if self.check_requirement() {
                info!("Ai {} is incanting", self.info.cli_id);
                self.incantate().await;
            }
        }
    }
}

impl Display for Queen {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "Queen => {}", self.info)
    }
}
