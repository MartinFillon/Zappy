//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// queen
//

use core::fmt;
use std::{fmt::{Display, Formatter}, future::IntoFuture};

use crate::{
    ai::{AIHandler, AI}, commands, elevation::{Config, Inventory}, tcp::command_handle::{self, CommandError, ResponseResult}
};

use super::AIState;
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
    look: LookInfo
}

impl Queen {
    /// Creates a new [`Queen`].
    pub fn new(info: AI) -> Self {
        let mut ai = Self { info, inv: Default::default(), look: Default::default() };
        ai.info.state = Some(AIState::Queen);
        ai
    }

    fn check_requirement(&self, requirement: &Config) -> bool
    {
        let idx = self.info.level - 1;
        let require = &requirement.elevation[idx];
        println!("{}", require);
        // Check the look response with the the requirement.
        true
    }

    fn to_look_info(&mut self, vec: Vec<String>)
    {
        self.look.inv.clear();

        let mut inv: &mut Inventory = &mut self.look.inv;

        println!("{:?}", vec);
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
                _ => ()
            }
        }
    }

    /// Transform Inventory info to exploit them later.
    fn to_inv(&mut self, vec: Vec<(String, i32)>)
    {
        for elem in vec.iter() {
            match elem.0.as_str() {
                "food" => self.inv.set_food(elem.1 as usize),
                "linemate" => self.inv.set_linemate(elem.1 as usize),
                "deraumere" => self.inv.set_deraumere(elem.1 as usize),
                "sibur" => self.inv.set_sibur(elem.1 as usize),
                "mendiane" => self.inv.set_mendiane(elem.1 as usize),
                "phiras" => self.inv.set_phiras(elem.1 as usize),
                "thystame" => self.inv.set_thystame(elem.1 as usize),
                _ => ()
            }
        }
    }
}

#[async_trait]
// Handle Eject DON'T FORGET.
impl AIHandler for Queen {
    fn init(&mut self, info: AI) -> Self {
        Self::new(info)
    }

    fn update(&mut self) {}

    async fn loop_ai(&mut self, requirement: Config) -> Result<(), command_handle::CommandError> {
        let mut i = 0;
        while i < 10 {
            let val = {
                let mut cli = self.info.client.lock().await;
                let val = commands::look_around::look_around(&mut cli).await?;
                val
            };
            match val {
                ResponseResult::Tiles(vec) => self.to_look_info(vec[0].clone()),
                _ => ()
            };

            let val = {
                let mut cli = self.info.client.lock().await;
                let val = commands::inventory::inventory(&mut cli).await?;
                val
            };
            match val {
                ResponseResult::Inventory(vec) => self.to_inv(vec),
                _ => ()
            };

            let _ = {
                let mut cli = self.info.client.lock().await;
                let val = commands::move_up::move_up(&mut cli).await?;
                val
            };
            // if self.check_requirement(&requirement) {
                // i += 1;
                // Incantation
            // }
        }
        Ok(())
    }
}

impl Display for Queen {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "Queen => {}", self.info)
    }
}

/*
    while 1 == 1 {
        Look ==> In the current Look array,
        Inventory ==> In the current inventory,
        if check_take_food() {
            Take food
        },
        if check_requirement() && check_enough_food() {
            Incantation
        }
    }
*/
