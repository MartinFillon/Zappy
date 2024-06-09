//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// knight
//

use crate::ai::{AIHandler, AI};
use crate::tcp::command_handle::CommandError;

#[derive(Debug, Clone)]
pub struct Knight {
    info: AI,
}

impl Knight {
    fn new(info: AI) -> Self {
        Self { info }
    }
}

impl AIHandler for Knight {
    fn init(&mut self, info: AI) -> Self {
        Self::new(info)
    }

    fn update(&mut self) {}
    async fn loop_ai(&mut self) -> Result<(), CommandError> {
        Ok(())
    }
}
