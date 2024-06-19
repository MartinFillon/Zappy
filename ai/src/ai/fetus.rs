//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// fetus
//

use crate::{
    ai::{start_ai, AIHandler, AI},
    commands::drop_object,
    tcp::{
        command_handle::{CommandError, ResponseResult},
        handle_tcp,
    },
};

use std::io::{self, Error};
use std::sync::Arc;

use async_trait::async_trait;
use tokio::sync::Mutex;

use log::{error, info};

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

    async fn fork_dupe(info: AI, set_id: Option<usize>) -> io::Result<()> {
        let c_id = info.cli_id + 1;
        let client = match handle_tcp(info.address.clone(), info.team.clone(), c_id).await {
            Ok(client) => {
                info!(
                    "[{}] New `Fetus` client connected successfully.",
                    info.cli_id
                );
                Arc::new(Mutex::new(client))
            }
            Err(e) => return Err(Error::new(e.kind(), e)),
        };

        let p_id = set_id.unwrap_or(0);
        let team = info.team.clone();
        let address = info.address.clone();

        match start_ai(client, team, address, (c_id, p_id), false).await {
            Ok(ai) => {
                let mut fetus = Fetus::init(ai.clone());
                if let Err(e) = fetus.update().await {
                    println!("[{}] Error: {}", c_id, e);
                }
                Ok(())
            }
            Err(e) => {
                error!("[{}] {}", c_id, e);
                Err(e)
            }
        }
    }
}
