//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// empress
//

use crate::{
    ai::{AIHandler, Incantationers, AI},
    commands::{self},
    elevation::{Config, Inventory},
    move_towards_broadcast::backtrack_eject,
    tcp::{
        command_handle::{self, CommandError, CommandHandler, ResponseResult},
        TcpClient,
    },
};

use async_trait::async_trait;

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
            commands::move_up::move_up(&mut cli).await?;
            commands::fork::fork(&mut cli).await?;
            // Here you can create a queen after the fork with `i` as id.
            println!("{i}");
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
        self.spawn_queens().await?;

        let mut cli = self.info.client.lock().await;
        commands::drop_object::drop_object(&mut cli, "food").await?;
        Ok(())
    }
}
