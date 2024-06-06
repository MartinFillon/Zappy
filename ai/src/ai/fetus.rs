//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// fetus
//

use crate::ai::{AIHandler, Action, AI};

#[derive(Debug, Clone, Default)]
pub struct Fetus {}

impl AIHandler for Fetus {
    fn init(&mut self, info: AI) -> Self {
        Self::default()
    }

    fn update(&mut self, action: Option<Action>) {}
}
