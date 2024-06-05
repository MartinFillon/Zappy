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

fn read_output(raw: String) -> Vec<Vec<String>> {
    let mut tiles: Vec<Vec<String>> = vec![];
    let tmp = raw.trim_matches(|c| c == '[' || c == ']' || c == '\n');

    for tile in tmp.split(',') {
        let mut tile_content: Vec<String> = vec![];
        for item in tile.split(' ') {
            tile_content.push(item.to_string());
        }
        tiles.push(tile_content);
    }
    info!("Tiles: {:?}", tiles);
    tiles
}

pub async fn look_around(client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
    info!("Looking around...");
    let response = client.check_dead("Look\n").await?;

    Ok(ResponseResult::Tiles(read_output(response)))
}
