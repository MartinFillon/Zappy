//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// commands
//

use crate::tcp::TcpClient;

#[async_trait]
pub trait CommandHandler {
    async fn send_command(&mut self, command: &str) -> Result<String, bool>;
    async fn check_dead(&mut self, command: &str) -> Result<String, bool>;
}

#[async_trait::async_trait]
impl CommandHandler for TcpClient {
    async fn send_command(&mut self, command: &str) -> Result<String, bool> {
        if self.send_request(command.to_string()).await.is_err() {
            return Err(true);
        }
        match self.get_response().await {
            Some(res) => Ok(res),
            None => Err(true),
        }
    }

    async fn check_dead(&mut self, command: &str) -> Result<String, bool> {
        let response = self.send_command(command).await?;
        if response == "dead\n" {
            return Err(false);
        }
        Ok(response)
    }
}
