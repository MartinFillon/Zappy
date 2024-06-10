//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// knight
//

use crate::{
    ai::{AIHandler, Incantationers, AI},
    commands,
    move_towards_broadcast::backtrack_eject,
    tcp::{
        command_handle::{CommandError, CommandHandler, DirectionEject, ResponseResult},
        TcpClient,
    },
};

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
        Ok(())
    }
}

#[async_trait]
impl Incantationers for Knight {
    async fn handle_eject(
        client: &mut TcpClient,
        res: Result<ResponseResult, CommandError>,
    ) -> Result<ResponseResult, CommandError> {
        if let Ok(ResponseResult::Eject(ref dir)) = res {
            if backtrack_eject(client, dir.clone()).await {
                let response = client.check_response().await?;
                client.handle_response(response).await?;
            }
        }
        res
    }
}
