//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// knight
//

use crate::ai::{AIHandler, AI};
use crate::commands;
use crate::tcp::command_handle::CommandError;

use async_trait::async_trait;

use log::info;

#[derive(Debug, Clone)]
pub struct Knight {
    info: AI,
}

impl Knight {
    fn new(info: AI) -> Self {
        Self { info }
    }
}

#[async_trait]
impl AIHandler for Knight {
    fn init(info: AI) -> Self {
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        let mut client_lock = self.info.client.lock().await;

        commands::inventory::inventory(&mut client_lock).await?;
        Ok(())
    }
}
