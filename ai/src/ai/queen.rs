//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// queen
//

use core::fmt;
use std::fmt::{Display, Formatter};

use crate::{
    ai::{AIHandler, AI}, commands, elevation::Config, tcp::command_handle::{self, CommandError}
};

use super::AIState;
use async_trait::async_trait;

#[derive(Debug, Clone)]
pub struct Queen {
    pub info: AI
}

impl Queen {
    /// Creates a new [`Queen`].
    pub fn new(info: AI) -> Self {
        let mut ai = Self { info };
        ai.info.state = Some(AIState::Queen);
        ai
    }

    fn check_requirement(&self, requirement: Config) -> bool
    {
        let idx = self.info.level - 1;
        let require = &requirement.elevation[idx];
        println!("{}", require);
        // Check the look response with the the requirement.
        true
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
        self.check_requirement(requirement);
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
        commands::move_up::move_up(self.info.client).await;
        commands::move_up::move_up(self.info.client).await;
        commands::move_up::move_up(self.info.client).await;
        commands::move_up::move_up(self.info.client).await;
        */
        Ok(())
    }
}

impl Display for Queen {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "Queen => {}", self.info)
    }
}
