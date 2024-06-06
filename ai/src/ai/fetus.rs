//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// fetus
//

use crate::ai::{AIHandler, AI};

#[derive(Debug, Clone, Default)]
pub struct Fetus {}

impl AIHandler for Fetus {
    fn init(&mut self, _info: AI) -> Self {
        Self::default()
    }

    fn update(&mut self) {}
}
