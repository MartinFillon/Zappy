//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// fetus
//

use crate::{
    ai::{AIHandler, AI},
    commands::drop_object,
    tcp::command_handle::{CommandError, ResponseResult},
};

use async_trait::async_trait;

use log::info;

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
        println!("[{}] Fetus spawned.", info.cli_id);
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        let mut client_lock = self.info.client.lock().await;
        let mut total = 0;

        loop {
            match drop_object::drop_object(&mut client_lock, "food").await {
                Ok(ResponseResult::OK) => {
                    total += 1;
                }
                Err(CommandError::DeadReceived) | Ok(ResponseResult::KO) => {
                    info!("[{}] Fetus dropped x{} food", self.info.cli_id, total);
                    println!("[{}] AI : Fetus died.", self.info.cli_id);
                    return Err(CommandError::DeadReceived);
                }
                _ => {
                    continue;
                }
            }
        }
    }
}
