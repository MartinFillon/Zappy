//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// empress
//

#![allow(dead_code)]
#![allow(unused_imports)]

use crate::{
    ai::{ai_create::start_queen_ai, AIHandler, Incantationers, AI},
    commands::{self, unused_slots},
    elevation::{Config, Inventory},
    move_towards_broadcast::backtrack_eject,
    tcp::{
        command_handle::{self, CommandError, CommandHandler, ResponseResult},
        TcpClient,
    },
};

use async_trait::async_trait;
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

        for i in 1..5 {
            println!("Creating Queen #{}", i);
            commands::move_up::move_up(&mut cli).await?;
            commands::fork::fork(&mut cli).await?;
            debug!("Task for new queen will start...");
            if let Err(err) = start_queen_ai(self.info().clone(), Some(i)).await {
                error!("{err}");
                return Err(CommandError::RequestError);
            }
            println!("Queen with id {i}");
        }
        commands::broadcast::broadcast(&mut cli, "Done").await?;
        Ok(())
    }
}

#[async_trait]
impl AIHandler for Empress {
    fn init(info: AI) -> Self {
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), command_handle::CommandError> {
        println!("I AM THE EMPRESS BOW UPPON ME");
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
}
