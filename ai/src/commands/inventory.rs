//
// EPITECH PROJECT, 2024
// inventory
// File description:
// inventory command
//

#![allow(dead_code)]

use crate::tcp::command_handle::{CommandError, CommandHandler, ResponseResult};
use crate::tcp::TcpClient;

use log::info;

fn read_output(raw: String) -> Vec<(String, i32)> {
    let mut inventory = Vec::new();
    let tmp = raw.trim_matches(|c| c == '[' || c == ']' || c == '\n');

    for tile in tmp.split(',') {
        if let Some(idex) = tile.rfind(' ') {
            let (item, quantity) = tile.split_at(idex);
            inventory.push((
                item.trim().to_string(),
                quantity.trim().parse::<i32>().unwrap_or(0),
            ));
        }
    }
    info!("Inventory: {:?}", inventory);
    inventory
}

pub async fn inventory(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    info!("Checking inventory...");
    let response = client.check_dead("Inventory\n").await?;
    if client.handle_response(response.clone()).await.is_err() {
        return Ok(ResponseResult::Inventory(read_output(response)));
    }
    Err(CommandError::InvalidResponse)
}
