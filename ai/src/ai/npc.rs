//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// ncp
//

use crate::{
    ai::{AIHandler, AI},
    tcp::command_handle::CommandError,
};

use async_trait::async_trait;

use zappy_macros::Bean;

#[derive(Debug, Clone, Bean)]
pub struct NPC {
    info: AI,
}

impl NPC {
    ///
    /// [`NPC`] initialize the struct with `AI` struct
    ///
    fn new(info: AI) -> Self {
        Self { info }
    }
}

#[async_trait]
impl AIHandler for NPC {
    ///
    /// Initializes the [`NPC`]
    ///
    /// * `info` - `AI` structure that represents the basic info of an AI client
    ///
    fn init(info: AI) -> Self {
        println!("-[{}] NPC spawned.", info.cli_id);
        Self::new(info)
    }

    ///
    /// [`NPC`]'s main loop
    ///
    async fn update(&mut self) -> Result<(), CommandError> {
        let mut client = self.info.client().lock().await;
        while let Some(response) = client.get_response().await {
            if response.trim_end() == "dead" {
                println!("-[{}] AI : NPC died.", self.info.cli_id);
                break;
            }
        }
        Ok(())
    }
}
