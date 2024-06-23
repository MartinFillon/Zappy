//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// fetus
//

use crate::{
    ai::{AIHandler, AI},
    commands::drop_object::drop_object,
    tcp::command_handle::{CommandError, ResponseResult},
};

use async_trait::async_trait;

#[allow(unused_imports)]
use log::{debug, error, info, warn};

use zappy_macros::Bean;

#[derive(Debug, Clone, Bean)]
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
        println!("-[{}] Fetus spawned.", info.cli_id);
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        let mut client_lock = self.info.client.lock().await;
        let mut total = 0;

        loop {
            match drop_object(&mut client_lock, "food").await {
                Ok(ResponseResult::OK) => {
                    total += 1;
                }
                Err(CommandError::DeadReceived) | Ok(ResponseResult::KO) => {
                    info!(
                        "-[{}] AI : Fetus died and dropped x{} food.",
                        self.info.cli_id, total
                    );
                    return Err(CommandError::DeadReceived);
                }
                _ => {
                    continue;
                }
            }
        }
    }
}

#[cfg(test)]
mod fetus_test {
    use super::*;
    use crate::ai::AI;
    use crate::tcp::TcpClient;

    use std::sync::Arc;
    use tokio::sync::Mutex;

    fn setup_fetus() -> Fetus {
        let client = TcpClient::new("127.0.0.1", "Team".to_string(), 1);
        let ai = AI {
            address: "127.0.0.1".to_string(),
            team: "Team".to_string(),
            cli_id: 1,
            p_id: 1,
            client: Arc::new(Mutex::new(client)),
            map: (10, 10),
            level: 1,
            slots: 0,
        };
        Fetus::new(ai)
    }

    #[tokio::test]
    async fn test_bot_init() {
        let fetus = setup_fetus();

        assert_eq!(fetus.info().cli_id, 1);
        assert_eq!(fetus.info().p_id, 1);
        assert_eq!(fetus.info().level, 1);
    }
}
