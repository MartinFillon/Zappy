//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// queen
//

use crate::ai::{AIHandler, AI};
use crate::tcp::command_handle::CommandError;

#[derive(Debug, Clone)]
pub struct Queen {
    info: AI,
}

impl Queen {
    fn new(info: AI) -> Self {
        Self { info }
    }
}

impl AIHandler for Queen {
    fn init(&mut self, info: AI) -> Self {
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        Ok(())
    }
}

impl Queen {
    // fn handle eject reset
}
