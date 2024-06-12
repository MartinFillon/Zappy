//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// bot
//

use std::mem::swap;

use crate::{
    ai::{AIHandler, AI},
    commands::{
        drop_object::drop_object,
        inventory::inventory,
        look_around::look_around,
        move_up::move_up,
        take_object::take_object,
        turn::{turn, DirectionTurn},
    },
    tcp::{
        command_handle::{
            CommandError, CommandHandler, DirectionEject, DirectionMessage, ResponseResult,
        },
        TcpClient,
    },
};

use async_trait::async_trait;

use log::info;
use zappy_macros::Bean;

use super::Listeners;

pub const COLONY_PLAYER_COUNT: usize = 2;
const MAX_MOVEMENTS: usize = 5;
static ITEM_PRIORITY: [(&str, usize); 7] = [
    ("food", 6),
    ("linemate", 1),
    ("deraumere", 2),
    ("sibur", 3),
    ("mendiane", 4),
    ("phiras", 5),
    ("thystame", 7),
];

#[derive(Debug, Clone, Bean)]
pub struct Bot {
    info: AI,
    coord: (i32, i32),
}

fn make_item_prioritary(item: &str) {
    swap(
        &mut ITEM_PRIORITY
            .iter()
            .max_by(|a, b| a.1.cmp(&b.1))
            .unwrap_or(&ITEM_PRIORITY[6]),
        &mut ITEM_PRIORITY
            .iter()
            .find(|i| i.0 == item)
            .unwrap_or(&("", 0)),
    )
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
            self.handle_message().await?;
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
        let (x, y) = (self.coord().0 + d.0, self.coord().1 + d.1);
        info!("Updating movement of offset: ({}, {})...", d.0, d.1);

        let (width, height) = (self.info.map().0 / 2, self.info.map().1 / 2);

        info!(
            "Coordinated updated from: ({}, {})",
            self.coord().0,
            self.coord().1
        );

        let wrapped_x = wrap_coordinate(x, width);
        let wrapped_y = wrap_coordinate(y, height);

        info!("To: ({}, {})", wrapped_x, wrapped_y);
        self.set_coord((wrapped_x, wrapped_y));
    }

    fn update_eject_coord(&mut self, direction: DirectionEject) {
        info!("Updating movement from Direction: {}...", direction);
        match direction {
            DirectionEject::North => self.update_coord_movement((0, 1)),
            DirectionEject::East => self.update_coord_movement((1, 0)),
            DirectionEject::South => self.update_coord_movement((0, -1)),
            DirectionEject::West => self.update_coord_movement((-1, 0)),
        }
    }

    pub async fn seek_objects(&mut self) -> Result<ResponseResult, CommandError> {
        let res = {
            let mut client_lock = self.info.client().lock().await;
            look_around(&mut client_lock).await?
        };
        match res {
            ResponseResult::Tiles(tiles) => {
                let mut best_item = String::new();
                let tile = {
                    let mut client_lock = self.info.client().lock().await;
                    seek_best_item_index(&mut client_lock, tiles, &mut best_item).await?
                };
                if best_item.is_empty() {
                    Ok(ResponseResult::KO)
                } else {
                    if !self.move_to_tile(tile).await {
                        return Err(CommandError::RequestError);
                    }
                    let mut client_lock = self.info.client().lock().await;
                    take_object(&mut client_lock, &best_item).await
                }
            }
            res => Ok(res),
        }
    }

    pub async fn drop_items(&mut self) -> Result<ResponseResult, CommandError> {
        loop {
            let mut client_lock = self.info.client().lock().await;
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
        let mut client_lock = self.info.client().lock().await;
        turn(&mut client_lock, DirectionTurn::Right).await?;
        turn(&mut client_lock, DirectionTurn::Right).await?;
        Ok(ResponseResult::OK)
    }

    pub async fn backtrack(&mut self) -> Result<ResponseResult, CommandError> {
        self.turn_around().await?;
        if self.coord().1.is_negative() {
            self.coord.1 = -self.coord().1;
        }
        if !self.move_ai_to_coords(*self.coord()).await {
            return Err(CommandError::RequestError);
        }
        self.set_coord((0, 0));
        Ok(ResponseResult::OK)
    }

    fn handle_queen_message(&self, msg: &str) -> Result<ResponseResult, CommandError> {
        match msg {
            "nf" => make_item_prioritary("food"),
            "nl" => make_item_prioritary("linemate"),
            "nd" => make_item_prioritary("deraumere"),
            "ns" => make_item_prioritary("sibur"),
            "nm" => make_item_prioritary("mendiane"),
            "np" => make_item_prioritary("phiras"),
            "nt" => make_item_prioritary("thystame"),
            _ => return Err(CommandError::InvalidResponse),
        }
        Ok(ResponseResult::OK)
    }

    async fn analyse_messages(&mut self, cli_id: &mut i32) -> Result<ResponseResult, CommandError> {
        let mut res = Ok(ResponseResult::OK);
        let mut client = self.info.client().lock().await;
        while let Some(message) = client.pop_message() {
            match message {
                (DirectionMessage::Center, msg) => {
                    if let Ok(id) = msg.parse::<i32>() {
                        cli_id.clone_from(&id);
                    }
                }
                (_, msg) => {
                    if !msg.contains(' ') || msg.len() < 2 {
                        continue;
                    }
                    if let Some(idex) = msg.trim_end_matches('\n').find(' ') {
                        let content = msg.split_at(idex);
                        if let Ok(id) = content.0.parse::<i32>() {
                            if id == *self.info().cli_id()
                                && self.handle_queen_message(content.1).is_err()
                            {
                                res = Err(CommandError::InvalidResponse);
                            }
                        }
                    }
                }
            }
        }
        res
    }
}

#[async_trait]
impl Listeners for Bot {
    async fn handle_message(&mut self) -> Result<ResponseResult, CommandError> {
        let mut id = -1;
        self.analyse_messages(&mut id).await?;
        if id != -1 {
            self.info.set_cli_id(id);
        }
        Ok(ResponseResult::OK)
    }
}

pub fn wrap_coordinate(coord: i32, max: i32) -> i32 {
    let mut wrapped = (coord % max + max) % max;
    if coord > max {
        wrapped = -(max - (wrapped - 1));
    } else if coord < -max {
        wrapped += 1;
    }
    wrapped
}
