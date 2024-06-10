//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// knight
//

use crate::ai::{utils, AIHandler, AI};
use crate::commands;
use crate::move_towards_broadcast::backtrack_eject;
use crate::tcp::command_handle::{CommandError, DirectionEject, ResponseResult};
use crate::tcp::TcpClient;

use async_trait::async_trait;

use log::info;

#[derive(Debug, Clone)]
pub struct Knight {
    info: AI,
}

impl Knight {
    fn new(info: AI) -> Self {
        Self { info }
    }
}

#[async_trait]
impl AIHandler for Knight {
    fn init(info: AI) -> Self {
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        let mut _client_lock = self.info.client.lock().await;

        Ok(())
    }
}

impl Knight {
    async fn handle_reject(
        &mut self,
        client: &mut TcpClient,
        res: Result<ResponseResult, CommandError>,
    ) -> Result<ResponseResult, CommandError> {
        if let Ok(ResponseResult::Eject(ref dir)) = res {
            if backtrack_eject(client, dir.clone()).await {
                return Ok(ResponseResult::EjectUndone);
            }
        }
        res
    }
}
