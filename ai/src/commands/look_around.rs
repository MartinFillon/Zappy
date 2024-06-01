//
// EPITECH PROJECT, 2024
// look_around
// File description:
// look around command
//

#![allow(dead_code)]

use crate::tcp::command_handle::{CommandError, CommandHandler, ResponseResult};
use crate::tcp::TcpClient;

use log::info;

fn read_output(raw: String) -> Vec<String> {
    let mut tiles = Vec::new();
    let tmp = raw.trim_matches(|c| c == '[' || c == ']' || c == '\n');

    for tile in tmp.split(',') {
        for item in tile.split(' ') {
            tiles.push(item.to_string());
        }
    }
    info!("Tiles: {:?}", tiles);
    tiles
}

pub async fn look_around(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    info!("Looking around...");
    let response = client.check_dead("Look\n").await?;

    Ok(ResponseResult::Tiles(read_output(response)))
}
