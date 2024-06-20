//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// bot
//

#![allow(dead_code)]

use crate::{
    ai::{start_ai, AIHandler, AI},
    commands::{
        drop_object::drop_object,
        inventory::inventory,
        look_around::look_around,
        take_object::{self, take_object},
        turn::{turn, DirectionTurn},
    },
    move_towards_broadcast::move_towards_broadcast,
    tcp::{
        command_handle::{CommandError, DirectionEject, DirectionMessage, ResponseResult},
        handle_tcp, TcpClient,
    },
};

use std::io::{self, Error};
use std::mem::swap;
use std::sync::Arc;

use async_trait::async_trait;
use rand::Rng;
use tokio::{sync::Mutex, task};

use log::{debug, error, info};
use zappy_macros::Bean;

use super::Listeners;

pub const COLONY_PLAYER_COUNT: usize = 2;
const MAX_MOVEMENTS: usize = 10;
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
    backtrack_infos: Vec<(i32, i32)>,
}

fn make_item_prioritised(item: &str) {
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

fn get_best_item_in_tile(tile: &[String], inv: &[(String, i32)]) -> (usize, String) {
    let mut best: usize = 0;
    for obj in tile {
        if obj.as_str() == "player" {
            continue;
        }
        let in_inv = inv.iter().position(|(item, _)| item == obj).unwrap_or(0); // check for (index out of bounds: the len is 0 but the index is 0)
        if inv[in_inv].0 != inv[best].0
            && inv[in_inv].1 < 3
            && get_item_priority(obj) > get_item_priority(inv[best].0.as_str())
        {
            best = in_inv;
        }
    }
    (best, inv[best].0.clone())
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
            for tile in tiles {
                let (pos, item) = get_best_item_in_tile(&tile, &inv);
                if get_item_priority(item.as_str()) > get_item_priority(inv[idex].0.as_str())
                    && player_count_on_tile(&tile) < COLONY_PLAYER_COUNT
                {
                    idex = pos;
                    best_item.clone_from(&item);
                }
            }
            Ok(idex)
        }
        _ => Err(CommandError::RequestError),
    }
}

fn done_dropping_items(inv: &[(String, i32)]) -> bool {
    for (item, count) in inv {
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
            backtrack_infos: Vec::new(),
        }
    }
}

#[async_trait]
impl AIHandler for Bot {
    fn init(info: AI) -> Self {
        println!("BOT HERE.");
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        let mut idex: usize = 0;
        loop {
            info!("Handling bot [Queen {}]...", self.info().p_id);
            let _ = self.handle_message().await;
            if idex > MAX_MOVEMENTS {
                let _ = self.backtrack().await;
                let _ = self.drop_items().await;
                for _ in 0..5 {
                    let mut client = self.info().client().lock().await;
                    let _ = take_object::take_object(&mut client, "food").await;
                }
                idex = 0;
                continue;
            }
            //if self.seek_objects().await? == ResponseResult::KO {
            let random: usize = rand::thread_rng().gen_range(1..=3);
            let _ = self.move_to_tile(random).await;
            {
                let mut client = self.info().client().lock().await;
                if let Ok(ResponseResult::Tiles(tiles)) = look_around(&mut client).await {
                    if player_count_on_tile(&tiles[0]) < COLONY_PLAYER_COUNT
                        && tiles[0].last().unwrap() != "player"
                    {
                        let _ = take_object(&mut client, tiles[0].last().unwrap().as_str()).await;
                    }
                }
            }
            //}
            idex += 1;
        }
    }

    async fn fork_dupe(info: AI, set_id: Option<usize>) -> io::Result<()> {
        let client: Arc<Mutex<TcpClient>> =
            match handle_tcp(info.address.clone(), info.team.clone()).await {
                Ok(client) => {
                    debug!("New `Bot` client connected successfully.");
                    Arc::new(Mutex::new(client))
                }
                Err(e) => return Err(Error::new(e.kind(), e)),
            };

        let c_id = info.cli_id;
        let p_id = set_id.unwrap_or(0);
        let team = info.team.clone();
        let address = info.address.clone();

        let handle = task::spawn(async move {
            match start_ai(client, team, address, (c_id, p_id), false).await {
                Ok(ai) => {
                    let mut bot = Bot::init(ai.clone());
                    if let Err(e) = bot.update().await {
                        println!("Error: {}", e);
                    }
                    Ok(ai)
                }
                Err(e) => {
                    error!("{}", e);
                    Err(e)
                }
            }
        });

        tokio::spawn(async move {
            if let Err(e) = handle.await {
                error!("Task failed: {:?}", e);
            }
        });

        Ok(())
    }
}

impl Bot {
    pub fn update_coord_movement(&mut self, d: (i32, i32)) {
        let (x, y) = (self.coord().0 + d.0, self.coord().1 + d.1);
        debug!("Updating movement of offset: ({}, {})...", d.0, d.1);

        let (width, height) = (self.info().map().0 / 2, self.info().map().1 / 2);

        debug!(
            "Coordinated updated from: ({}, {})",
            self.coord().0,
            self.coord().1
        );

        let wrapped_x = wrap_coordinate(x, width);
        let wrapped_y = wrap_coordinate(y, height);

        debug!("To: ({}, {})", wrapped_x, wrapped_y);
        self.set_coord((wrapped_x, wrapped_y));
        self.backtrack_infos.push(d);
    }

    fn update_eject_coord(&mut self, direction: DirectionEject) {
        debug!("Updating movement from Direction: {}...", direction);
        match direction {
            DirectionEject::North => self.update_coord_movement((0, 1)),
            DirectionEject::East => self.update_coord_movement((1, 0)),
            DirectionEject::South => self.update_coord_movement((0, -1)),
            DirectionEject::West => self.update_coord_movement((-1, 0)),
        }
    }

    pub async fn seek_objects(&mut self) -> Result<ResponseResult, CommandError> {
        let res = {
            let mut client = self.info().client().lock().await;
            look_around(&mut client).await?
        };
        match res {
            ResponseResult::Tiles(tiles) => {
                let mut best_item = String::new();
                let tile = {
                    let mut client = self.info().client().lock().await;
                    seek_best_item_index(&mut client, tiles, &mut best_item).await?
                };
                if best_item.is_empty() {
                    Ok(ResponseResult::KO)
                } else {
                    let _ = self.move_to_tile(tile).await;
                    let mut client = self.info().client().lock().await;
                    take_object(&mut client, &best_item).await
                }
            }
            res => Ok(res),
        }
    }

    pub async fn drop_items(&mut self) -> Result<ResponseResult, CommandError> {
        let mut client = self.info().client().lock().await;
        if let Ok(ResponseResult::Inventory(inv)) = inventory(&mut client).await {
            for (item, mut count) in inv {
                while item.as_str() != "food" && count > 0 {
                    let _ = drop_object(&mut client, item.as_str()).await;
                    count -= 1;
                }
            }
            println!("Bot {} done dropping items.", self.info.p_id);
        }
        Ok(ResponseResult::OK)
    }

    async fn turn_around(&mut self) -> Result<ResponseResult, CommandError> {
        let mut client = self.info().client().lock().await;
        let _ = turn(&mut client, DirectionTurn::Right).await;
        let _ = turn(&mut client, DirectionTurn::Right).await;
        Ok(ResponseResult::OK)
    }

    pub async fn backtrack(&mut self) -> Result<ResponseResult, CommandError> {
        info!("Bot [Queen {}]: backtracking...", self.info().p_id);
        let _ = self.turn_around().await;
        while !self.backtrack_infos.is_empty() {
            let coords = self.backtrack_infos.pop().unwrap_or((0, 0));
            let _ = self.move_ai_to_coords(coords).await;
        }
        self.set_coord((0, 0));
        Ok(ResponseResult::OK)
    }

    async fn analyse_messages(&mut self, p_id: &mut usize) -> Result<ResponseResult, CommandError> {
        let res = Ok(ResponseResult::OK);
        let mut client = self.info().client().lock().await;
        while let Some(message) = client.pop_message() {
            info!(
                "Bot [Queen {}]: handling message: {}",
                self.info().p_id,
                message.1
            );
            match message {
                (DirectionMessage::Center, msg) => {
                    if let Ok(id) = msg.parse::<usize>() {
                        p_id.clone_from(&id);
                    }
                }
                (dir, msg) => {
                    if !msg.contains(' ') || msg.len() < 2 {
                        continue;
                    }
                    if let Some(idex) = msg.trim_end_matches('\n').find(' ') {
                        let content = msg.split_at(idex);
                        if let Ok(id) = content.0.parse::<usize>() {
                            if id == *self.info().p_id() {
                                handle_queen_message(&mut client, (dir, content.1.trim_start())).await?;
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
        let mut id: usize = 0;
        self.analyse_messages(&mut id).await?;
        if id != 0 {
            self.info.set_p_id(id);
        }
        Ok(ResponseResult::OK)
    }
}

async fn handle_queen_message(
    client: &mut TcpClient,
    (dir, msg): (DirectionMessage, &str),
) -> Result<ResponseResult, CommandError> {
    match msg {
        "mv" => return move_towards_broadcast(client, dir).await,
        "nf" => make_item_prioritised("food"),
        "nl" => make_item_prioritised("linemate"),
        "nd" => make_item_prioritised("deraumere"),
        "ns" => make_item_prioritised("sibur"),
        "nm" => make_item_prioritised("mendiane"),
        "np" => make_item_prioritised("phiras"),
        "nt" => make_item_prioritised("thystame"),
        _ => {}
    }
    Ok(ResponseResult::OK)
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
