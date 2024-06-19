//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// empress
//

#![allow(dead_code)]

use crate::{
    ai::{queen::Queen, start_ai, AIHandler, AI},
    commands::{self, unused_slots},
    tcp::{
        command_handle::{self, CommandError, ResponseResult},
        handle_tcp,
    },
};

use std::io::{self, Error};
use std::sync::Arc;

use async_trait::async_trait;
use tokio::sync::Mutex;

use log::{debug, error, info, warn};
use zappy_macros::Bean;

#[derive(Bean)]
pub struct Empress {
    pub info: AI,
    id: usize,
}

impl Empress {
    /// Creates a new [`Empress`].
    fn new(info: AI) -> Self {
        Self { info, id: 0_usize }
    }

    async fn spawn_queens(&mut self) -> Result<(), command_handle::CommandError> {
        let mut cli = self.info.client.lock().await;

        for i in 1..=4 {
            println!("Creating Queen #{}", i);
            while let Ok(ResponseResult::KO) = commands::fork::fork(&mut cli).await {
                error!("Fork received a KO.");
            }

            debug!("Task for new queen will start...");
            let info = self.info.clone();
            tokio::spawn(async move {
                if let Err(err) = Queen::fork_dupe(info, Some(i)).await {
                    error!("Queen fork error: {}", err);
                } else {
                    println!("Queen with id {i} created.");
                }
            });
            commands::move_up::move_up(&mut cli).await?;
        }
        println!("Done creating queens, broadcasting \"Done\".");
        commands::broadcast::broadcast(&mut cli, "Done").await?;
        Ok(())
    }
}

#[async_trait]
impl AIHandler for Empress {
    fn init(info: AI) -> Self {
        println!("I AM THE EMPRESS BOW UPPON ME");
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), command_handle::CommandError> {
        {
            let mut client = self.info().client().lock().await;
            while let ResponseResult::Value(val) = unused_slots::unused_slots(&mut client).await? {
                debug!("Blocked... Connect_nbr responds with [{}].", val);
                if val == 0 {
                    break;
                }
            }
        }
        info!("Starting spawning of queens...");
        self.spawn_queens().await?;
        warn!("Empress is now dying...");
        Err(CommandError::DeadReceived)
    }

    async fn fork_dupe(info: AI, set_id: Option<usize>) -> io::Result<()> {
        let c_id = info.cli_id + 1;
        let client = match handle_tcp(info.address.clone(), info.team.clone(), c_id).await {
            Ok(client) => {
                debug!("New `Empress` client connected successfully.");
                Arc::new(Mutex::new(client))
            }
            Err(e) => return Err(Error::new(e.kind(), e)),
        };

        let p_id = set_id.unwrap_or(0);
        let team = info.team.clone();
        let address = info.address.clone();

        match start_ai(client, team, address, (c_id, p_id), false).await {
            Ok(ai) => {
                let mut empress = Empress::init(ai.clone());
                if let Err(e) = empress.update().await {
                    println!("Error: {}", e);
                }
                Ok(())
            }
            Err(e) => {
                error!("{}", e);
                Err(e)
            }
        }
    }
}
