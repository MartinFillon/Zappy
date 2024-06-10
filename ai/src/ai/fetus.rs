//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// fetus
//

use crate::ai::{AIHandler, AI};
use crate::commands;
use crate::tcp::command_handle::{CommandError, ResponseResult};

use async_trait::async_trait;

#[derive(Debug, Clone)]
pub struct Fetus {
    info: AI,
}

impl Fetus {
    fn new(info: AI) -> Self {
        Self { info }
    }
}

#[async_trait]
impl AIHandler for Fetus {
    fn init(info: AI) -> Self {
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        let mut client_lock = self.info.client.lock().await;

        while let Ok(ResponseResult::OK) =
            commands::drop_object::drop_object(&mut client_lock, "food").await
        {
            println!("Dropping food x1...");
            commands::drop_object::drop_object(&mut client_lock, "food").await?;
        }
        Ok(())
    }
}
