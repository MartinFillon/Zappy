//
// EPITECH PROJECT, 2024
// bot.rs
// File description:
// ai bot role related functions
//

use crate::{
    commands::{self, look_around::look_around, take_object::take_object},
    move_to_tile::move_to_tile,
    tcp::{
        command_handle::{CommandError, ResponseResult},
        TcpClient,
    },
};
use log::info;

const ITEM_PRIORITY: [(&str, usize); 7] = [
    ("food", 6),
    ("linemate", 1),
    ("deraumere", 2),
    ("sibur", 3),
    ("mendiane", 4),
    ("phiras", 5),
    ("thystame", 7),
];

#[allow(dead_code)]
pub struct Bot {
    level: usize,
    pos: (i32, i32),
    key: String,
}

#[allow(dead_code)]
fn get_item_priority(item: &str) -> usize {
    ITEM_PRIORITY
        .iter()
        .find(|i| i.0 == item)
        .unwrap_or(&("", 0))
        .1
}

#[allow(dead_code)]
fn get_best_item_in_tile(tile: &[String], inv: &[(String, i32)]) -> Option<String> {
    let mut best = String::new();
    for obj in tile {
        if obj.as_str() == "player" {
            continue;
        }
        let in_inv = inv.iter().find(|(item, _)| item == obj).unwrap_or(&inv[0]);
        if in_inv.0 != best
            && in_inv.1 < 3
            && get_item_priority(obj) > get_item_priority(best.as_str())
        {
            best.clone_from(obj);
        }
    }
    if best.is_empty() {
        None
    } else {
        Some(best)
    }
}

#[allow(dead_code)]
impl Bot {
    async fn seek_best_item_index(
        client: &mut TcpClient,
        tiles: Vec<Vec<String>>,
        best_item: &mut String,
    ) -> Result<usize, CommandError> {
        match commands::inventory::inventory(client).await? {
            ResponseResult::Inventory(inv) => {
                let mut idex = 0;
                for (i, tile) in tiles.iter().enumerate() {
                    match get_best_item_in_tile(tile, &inv) {
                        Some(item) => {
                            if get_item_priority(item.as_str())
                                > get_item_priority(inv[idex].0.as_str())
                            {
                                idex = i;
                                best_item.clone_from(&item);
                            }
                        }
                        None => continue,
                    }
                }
                Ok(idex)
            }
            _ => Err(CommandError::RequestError),
        }
    }

    async fn seek_objects(&self, client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
        match look_around(client).await? {
            ResponseResult::Tiles(tiles) => {
                let mut best_item = String::new();
                let tile = Self::seek_best_item_index(client, tiles, &mut best_item).await?;
                if !move_to_tile(client, tile, self.level).await {
                    return Err(CommandError::RequestError);
                }
                take_object(client, &best_item).await
            }
            res => Ok(res),
        }
    }

    pub async fn handle_behavior(
        &self,
        client: &mut TcpClient,
    ) -> Result<ResponseResult, CommandError> {
        info!("Handling bot...");
        self.seek_objects(client).await
    }
}
