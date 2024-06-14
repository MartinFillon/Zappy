//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// empress
//

#![allow(dead_code)]
#![allow(unused_imports)]

use crate::{
    ai::{queen::Queen, start_ai, AIHandler, Incantationers, AI},
    commands::{self, unused_slots},
    elevation::{Config, Inventory},
    move_towards_broadcast::backtrack_eject,
    tcp::{
        command_handle::{self, CommandError, CommandHandler, ResponseResult},
        handle_tcp, TcpClient,
    },
};

use std::io::{self, Error, ErrorKind};
use std::sync::Arc;

use async_trait::async_trait;
use tokio::{sync::Mutex, task};

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
            while let Ok(ResponseResult::KO) = commands::fork::fork(&mut cli).await {
                error!("Fork received a KO.");
            }
            debug!("Task for new queen will start...");
            if let Err(err) = Queen::fork_dupe(self.info.clone(), Some(i)).await {
                error!("Queen fork error: {}", err);
                // return Err(CommandError::RequestError);
            }
            println!("Queen with id {i} created.");
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

    async fn fork_dupe(info: AI, set_id: Option<usize>) -> io::Result<AI> {
        match handle_tcp(info.address.clone(), info.team.clone()).await {
            Ok(client) => {
                debug!("New `Empress` client connected successfully.");
                let client = Arc::new(Mutex::new(client));
                let (c_id, p_id) = (info.cli_id, set_id.unwrap_or(0));
                let team = info.team.clone();

                let handle = task::spawn(async move {
                    match start_ai(
                        client.clone(),
                        team.to_string(),
                        info.address,
                        (c_id, p_id),
                        false,
                    )
                    .await
                    {
                        Ok(ai) => {
                            let mut empress: Empress = Empress::init(ai.clone());
                            if let Err(e) = empress.update().await {
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
                    Ok(ai) => return ai,
                    Err(e) => error!("Task failed: {:?}", e),
                }
            }
            Err(e) => {
                return Err(Error::new(e.kind(), e));
            }
        };
        Err(Error::new(
            ErrorKind::ConnectionRefused,
            "Couldn't reach host.",
        ))
    }
}
