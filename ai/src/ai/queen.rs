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
    tcp::command_handle,
};

use super::AIState;

#[derive(Debug, Clone)]
pub struct Queen {
    pub info: AI,
}

impl Queen {
    /// Creates a new [`Queen`].
    pub fn new(info: AI) -> Self {
        let mut ai = Self { info };
        ai.info.state = Some(AIState::Queen);
        ai
    }

    fn check_requirement() {}
}

impl AIHandler for Queen {
    fn init(&mut self, info: AI) -> Self {
        Self::new(info)
    }

    fn update(&mut self) {}

    async fn loop_ai(&mut self) -> Result<(), command_handle::CommandError> {
        // Handle Eject.
        // while 1 == 1 {
        // match {
        //     check_requirement => Incantation,
        //     Inventory,
        // }
        // }
        // commands::move_up::move_up(self.info.client).await;
        // commands::move_up::move_up(self.info.client).await;
        // commands::move_up::move_up(self.info.client).await;
        // commands::move_up::move_up(self.info.client).await;
        Ok(())
    }
}

impl Display for Queen {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "Queen => {}", self.info)
    }
}
