//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// bot
//

use crate::ai::{utils, AIHandler, AI};
use crate::commands::drop_object::drop_object;
use crate::commands::inventory::inventory;
use crate::commands::look_around::look_around;
use crate::commands::move_up::move_up;
use crate::commands::take_object::take_object;
use crate::commands::turn::{turn, DirectionTurn};
use crate::tcp::command_handle::{CommandError, Direction, ResponseResult};
use crate::tcp::TcpClient;

use async_trait::async_trait;

use log::info;

pub const COLONY_PLAYER_COUNT: usize = 2;
const MAX_MOVEMENTS: usize = 5;
const ITEM_PRIORITY: [(&str, usize); 7] = [
    ("food", 6),
    ("linemate", 1),
    ("deraumere", 2),
    ("sibur", 3),
    ("mendiane", 4),
    ("phiras", 5),
    ("thystame", 7),
];

#[derive(Debug, Clone)]
pub struct Bot {
    pub info: AI,
    pub coord: (i32, i32),
}

fn get_item_priority(item: &str) -> usize {
    ITEM_PRIORITY
        .iter()
        .find(|i| i.0 == item)
        .unwrap_or(&("", 0))
        .1
}

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

fn player_count_on_tile(tile: &[String]) -> usize {
    tile.iter().filter(|obj| obj.as_str() == "player").count()
}

async fn seek_best_item_index(
    client: &mut TcpClient,
    tiles: Vec<Vec<String>>,
    best_item: &mut String,
) -> Result<usize, CommandError> {
    match inventory(client).await? {
        ResponseResult::Inventory(inv) => {
            let mut idex = 0;
            for (i, tile) in tiles.iter().enumerate() {
                match get_best_item_in_tile(tile, &inv) {
                    Some(item) => {
                        if get_item_priority(item.as_str())
                            > get_item_priority(inv[idex].0.as_str())
                            && player_count_on_tile(tile) < COLONY_PLAYER_COUNT
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

fn done_dropping_items(inv: &[(String, i32)]) -> bool {
    for (item, count) in inv {
        if item.as_str() == "food" && *count > 5 {
            return false;
        }
        if item.as_str() != "food" && *count > 0 {
            return false;
        }
    }
    true
}

impl Bot {
    fn new(info: AI) -> Self {
        Self {
            info,
            coord: (0, 0),
        }
    }
}

#[async_trait]
impl AIHandler for Bot {
    fn init(info: AI) -> Self {
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        info!("Handling bot...");
        let mut idex: usize = 0;
        loop {
            if idex >= MAX_MOVEMENTS {
                self.backtrack().await?;
                self.drop_items().await?;
                break;
            }
            if self.seek_objects().await? != ResponseResult::KO {
                break;
            }
            idex += 1;
        }
        Ok(())
    }
}

impl Bot {
    pub fn update_coord_movement(&mut self, d: (i32, i32)) {
        let (x, y) = (self.coord.0 + d.0, self.coord.1 + d.1);
        info!("Updating movement of offset: ({}, {})...", d.0, d.1);

        let (width, height) = (self.info.map.0 / 2, self.info.map.1 / 2);

        info!(
            "Coordinated updated from: ({}, {})",
            self.coord.0, self.coord.1
        );

        let wrapped_x = utils::wrap_coordinate(x, width);
        let wrapped_y = utils::wrap_coordinate(y, height);

        info!("To: ({}, {})", wrapped_x, wrapped_y);
    }

    pub fn update_eject_coord(&mut self, direction: Direction) {
        info!("Updating movement from Direction: {}...", direction);
        match direction {
            Direction::Center => self.update_coord_movement((0, 0)),
            Direction::North => self.update_coord_movement((0, 1)),
            Direction::NorthWest => self.update_coord_movement((-1, 1)),
            Direction::West => self.update_coord_movement((-1, 0)),
            Direction::SouthWest => self.update_coord_movement((-1, -1)),
            Direction::South => self.update_coord_movement((0, -1)),
            Direction::SouthEast => self.update_coord_movement((1, -1)),
            Direction::East => self.update_coord_movement((1, 0)),
            Direction::NorthEast => self.update_coord_movement((1, 1)),
        }
    }

    pub async fn seek_objects(&mut self) -> Result<ResponseResult, CommandError> {
        let res = {
            let mut client_lock = self.info.client.lock().await;
            look_around(&mut client_lock).await?
        };
        match res {
            ResponseResult::Tiles(tiles) => {
                let mut best_item = String::new();
                let tile = {
                    let mut client_lock = self.info.client.lock().await;
                    seek_best_item_index(&mut client_lock, tiles, &mut best_item).await?
                };
                if best_item.is_empty() {
                    Ok(ResponseResult::KO)
                } else {
                    if !self.move_to_tile(tile).await {
                        return Err(CommandError::RequestError);
                    }
                    let mut client_lock = self.info.client.lock().await;
                    take_object(&mut client_lock, &best_item).await
                }
            }
            res => Ok(res),
        }
    }

    pub async fn drop_items(&mut self) -> Result<ResponseResult, CommandError> {
        loop {
            let mut client_lock = self.info.client.lock().await;
            match inventory(&mut client_lock).await? {
                ResponseResult::Inventory(inv) => {
                    if done_dropping_items(&inv) {
                        return Ok(ResponseResult::OK);
                    }
                    for (item, count) in inv {
                        if (item.as_str() == "food" && count > 5)
                            || (item.as_str() != "food" && count > 0)
                        {
                            match drop_object(&mut client_lock, item.as_str()).await? {
                                ResponseResult::OK => {}
                                res => return Ok(res),
                            }
                        }
                    }
                }
                res => return Ok(res),
            }
        }
    }

    async fn turn_around(&mut self) -> Result<ResponseResult, CommandError> {
        let mut client_lock = self.info.client.lock().await;
        turn(&mut client_lock, DirectionTurn::Right).await?;
        turn(&mut client_lock, DirectionTurn::Right).await?;
        Ok(ResponseResult::OK)
    }

    pub async fn backtrack(&mut self) -> Result<ResponseResult, CommandError> {
        self.turn_around().await?;
        if self.coord.1.is_negative() {
            self.coord.1 = -self.coord.1;
        }
        if !self.move_ai_to_coords(self.coord).await {
            return Err(CommandError::RequestError);
        }
        self.coord = (0, 0);
        Ok(ResponseResult::OK)
    }
}
