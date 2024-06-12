//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// queen
//

use crate::{
    ai::{AIHandler, Incantationers, AI},
    commands,
    elevation::{Config, Inventory},
    move_towards_broadcast::backtrack_eject,
    tcp::{
        command_handle::{self, CommandError, CommandHandler, ResponseResult},
        TcpClient,
    },
};

use core::fmt;
use std::fmt::{Display, Formatter};

use async_trait::async_trait;

use log::info;

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
}

impl Queen {
    /// Creates a new [`Queen`].
    fn new(info: AI) -> Self {
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

        let mut val = commands::incantation::incantation(&mut cli).await;
        val = Queen::handle_eject(&mut cli, val).await;
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

    async fn fork_servant(&mut self) -> Result<(), command_handle::CommandError> {
        let mut cli = self.info.client.lock().await;
        commands::fork::fork(&mut cli).await?;

        // PlaceHolder for Knight creation
        commands::broadcast::broadcast(&mut cli, format!("{}", 0).as_str()).await?;
        info!("I as the queen ({}), bestow my life uppon you\n", 0);

        commands::fork::fork(&mut cli).await?;
        // PlaceHolder for Bot creation

        commands::fork::fork(&mut cli).await?;
        // PlaceHolder for Bot creation

        info!("Miserable peasants... Serve me.\n");

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
}

#[async_trait]
impl AIHandler for Queen {
    fn init(info: AI) -> Self {
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), command_handle::CommandError> {
        self.fork_servant().await?;
        loop {
            let val = {
                let mut cli = self.info.client.lock().await;
                let res = commands::look_around::look_around(&mut cli).await;
                Queen::handle_eject(&mut cli, res).await
            };
            if let Ok(ResponseResult::Tiles(vec)) = val {
                self.convert_to_look_info(vec[0].clone());
            }

            let val = {
                let mut cli = self.info.client.lock().await;
                let res = commands::inventory::inventory(&mut cli).await;
                Queen::handle_eject(&mut cli, res).await
            };
            if let Ok(ResponseResult::Inventory(vec)) = val {
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
