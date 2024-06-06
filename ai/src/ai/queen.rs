//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// queen
//

use crate::ai::{AIHandler, AI};

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

    fn update(&mut self) {}
}
