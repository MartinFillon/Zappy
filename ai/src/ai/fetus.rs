//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// fetus
//

use crate::{
    ai::{start_ai, AIHandler, AI},
    commands,
    tcp::{
        command_handle::{CommandError, ResponseResult},
        handle_tcp,
    },
};

use std::io::{self, Error, ErrorKind};
use std::sync::Arc;

use async_trait::async_trait;
use tokio::{sync::Mutex, task};

use log::{debug, error, info};

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
                info!("AI #{}: Fetus dropping food x1...", self.info.cli_id);
                total += 1;
            } else if command.is_err() {
                info!("Fetus dropped x{} food", total);
                println!("AI #{}: Fetus died.", self.info.cli_id);
                return Err(CommandError::DeadReceived);
            } else {
                continue;
            }
        }
    }

    async fn fork_dupe(info: AI, set_id: Option<usize>) -> io::Result<AI> {
        let client = match handle_tcp(info.address.clone(), info.team.clone()).await {
            Ok(client) => {
                debug!("New `Fetus` client connected successfully.");
                Arc::new(Mutex::new(client))
            }
            Err(e) => return Err(Error::new(e.kind(), e)),
        };

        let c_id = info.cli_id;
        let p_id = set_id.unwrap_or(0);
        let team = info.team.clone();
        let address = info.address.clone();

        let handle = task::spawn(async move {
            match start_ai(client, team, address, (c_id, p_id), false).await {
                Ok(ai) => {
                    let mut fetus = Fetus::init(ai.clone());
                    if let Err(e) = fetus.update().await {
                        println!("Error: {}", e);
                    }
                    Ok(ai)
                }
                Err(e) => {
                    error!("{}", e);
                    Err(e)
                }
            }
        });

        match handle.await {
            Ok(ai) => ai,
            Err(e) => {
                error!("Task failed: {:?}", e);
                Err(Error::new(ErrorKind::Other, "Task failed"))
            }
        }
    }
}
