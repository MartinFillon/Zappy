//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// fetus
//

use crate::ai::{AIHandler, AI};
use crate::commands;
use crate::tcp::command_handle::{CommandError, ResponseResult};
use crate::tcp::{self, TcpClient};

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
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        let mut client_lock = self.info.client.lock().await;
        let mut total = 0;

        loop {
            let command = commands::drop_object::drop_object(&mut client_lock, "food").await;
            if let Ok(ResponseResult::OK) = command {
                println!("AI #{}: Fetus dropping food x1...", self.info.cli_id);
                total += 1;
            } else if let Err(e) = command {
                info!("Fetus dropped x{} food", total);
                println!("AI #{}: Fetus died.", self.info.cli_id);
                return Err(e);
            } else {
                continue;
            }
        }
    }
}
