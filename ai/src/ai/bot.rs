//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// bot
//

#![allow(dead_code)]

use crate::{
    ai::{AIHandler, Listeners, AI},
    commands::{
        drop_object::drop_object,
        inventory::inventory,
        look_around::look_around,
        take_object::take_object,
        turn::{turn, DirectionTurn},
    },
    move_towards_broadcast::move_towards_broadcast,
    tcp::{
        command_handle::{CommandError, DirectionEject, DirectionMessage, ResponseResult},
        TcpClient,
    },
};

use rand::Rng;

use async_trait::async_trait;

#[allow(unused_imports)]
use log::{debug, error, info, warn};

use zappy_macros::Bean;

const REFILL_FOOD: usize = 8;

pub const COLONY_PLAYER_COUNT: usize = 8;
const MAX_MOVEMENTS: usize = 10;

#[derive(Debug, Clone, Bean)]
pub struct Bot {
    info: AI,
    coord: (i32, i32),
    backtrack_infos: Vec<(i32, i32)>,
}

#[async_trait]
impl AIHandler for Bot {
    fn init(info: AI) -> Self {
        println!("-[{}] BOT here.", info.cli_id);
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        info!(
            "-[{}] Bot [Queen {}] is now being handled...",
            self.info().cli_id,
            self.info().p_id
        );
        let mut idex: usize = 0;
        loop {
            self.handle_message().await?;
            if idex > MAX_MOVEMENTS {
                self.backtrack().await?;
                self.drop_items().await?;
                for _ in 0..=REFILL_FOOD {
                    let mut client = self.info().client().lock().await;
                    take_object(&mut client, "food").await?;
                }
                idex = 0;
                continue;
            }
            let random: usize = rand::thread_rng().gen_range(1..=3);
            self.move_to_tile(random).await?;
            self.seek_objects().await?;
            idex += 1;
        }
    }
}

fn player_count_on_tile(tile: &[String]) -> usize {
    tile.iter().filter(|obj| obj.as_str() == "player").count()
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

impl Bot {
    pub fn update_coord_movement(&mut self, d: (i32, i32)) {
        let (x, y) = (self.coord().0 + d.0, self.coord().1 + d.1);
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

    pub async fn seek_objects(&mut self) -> Result<(), CommandError> {
        let mut client = self.info().client().lock().await;
        if let Ok(ResponseResult::Tiles(tiles)) = look_around(&mut client).await {
            if player_count_on_tile(&tiles[0]) < COLONY_PLAYER_COUNT
                && tiles[0].last().unwrap_or(&String::from("player")) != "player"
            {
                if tiles[0].contains(&"phiras".to_owned()) {
                    take_object(&mut client, "phiras").await?;
                } else if tiles[0].contains(&"sibur".to_owned()) {
                    take_object(&mut client, "sibur").await?;
                } else {
                    take_object(&mut client, tiles[0].last().unwrap().as_str()).await?;
                }
            }
        }
        Ok(())
    }

    pub async fn drop_items(&mut self) -> Result<ResponseResult, CommandError> {
        let mut client = self.info().client().lock().await;
        if let Ok(ResponseResult::Inventory(inv)) = inventory(&mut client).await {
            for (item, mut count) in inv {
                while item.as_str() != "food" && count > 0 {
                    drop_object(&mut client, item.as_str()).await?;
                    count -= 1;
                }
            }
            info!(
                "-[{}] Bot {} done dropping items.",
                self.info.cli_id, self.info.p_id
            );
        }
        Ok(ResponseResult::OK)
    }

    async fn turn_around(&mut self) -> Result<ResponseResult, CommandError> {
        let mut client = self.info().client().lock().await;
        turn(&mut client, DirectionTurn::Right).await?;
        turn(&mut client, DirectionTurn::Right).await?;
        Ok(ResponseResult::OK)
    }

    pub async fn backtrack(&mut self) -> Result<ResponseResult, CommandError> {
        info!(
            "-[{}] Bot [Queen {}]: backtracking...",
            self.info().cli_id,
            self.info().p_id
        );
        self.turn_around().await?;
        while !self.backtrack_infos.is_empty() {
            let coords = self.backtrack_infos.pop().unwrap_or((0, 0));
            self.move_ai_to_coords(coords).await?;
        }
        self.set_coord((0, 0));
        Ok(ResponseResult::OK)
    }

    async fn analyse_messages(&mut self) -> Result<ResponseResult, CommandError> {
        let mut client = self.info().client().lock().await;
        while let Some(message) = client.pop_message() {
            debug!(
                "-[{}] Bot [Queen {}]: handling message: {}",
                self.info().cli_id,
                self.info().p_id,
                message.1
            );
            let (dir, msg) = message;
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
        Ok(ResponseResult::OK)
    }
}

#[async_trait]
impl Listeners for Bot {
    async fn handle_message(&mut self) -> Result<ResponseResult, CommandError> {
        self.analyse_messages().await?;
        Ok(ResponseResult::OK)
    }
}

async fn handle_queen_message(
    client: &mut TcpClient,
    (dir, msg): (DirectionMessage, &str),
) -> Result<ResponseResult, CommandError> {
    if msg == "mv" {
        return move_towards_broadcast(client, dir).await;
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

#[cfg(test)]
mod bot_test {
    use super::*;
    use crate::ai::AI;
    use crate::tcp::TcpClient;

    use std::sync::Arc;
    use tokio::sync::Mutex;

    #[test]
    fn test_wrap_coordinate() {
        assert_eq!(wrap_coordinate(5, 10), 5);
        assert_eq!(wrap_coordinate(-5, 10), 5);

        assert_eq!(wrap_coordinate(10, 10), 0);
        assert_eq!(wrap_coordinate(-10, 10), 0);

        assert_eq!(wrap_coordinate(15, 10), -6);
        assert_eq!(wrap_coordinate(20, 10), -11);

        assert_eq!(wrap_coordinate(-15, 10), 6);
        assert_eq!(wrap_coordinate(-20, 10), 1);

        assert_eq!(wrap_coordinate(0, 10), 0);
        assert_eq!(wrap_coordinate(10, 1), -2);
        assert_eq!(wrap_coordinate(-10, 1), 1);
    }

    fn setup_bot() -> Bot {
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
        Bot::new(ai)
    }

    #[test]
    fn test_update_coord_movement() {
        let mut bot = setup_bot();
        bot.update_coord_movement((1, 1));
        assert_eq!(*bot.coord(), (1, 1));

        bot.update_coord_movement((-2, -2));
        assert_eq!(*bot.coord(), (4, 4));
    }

    #[test]
    fn test_update_eject_coord() {
        let mut bot = setup_bot();
        bot.update_eject_coord(DirectionEject::North);
        assert_eq!(*bot.coord(), (0, 1));

        bot.update_eject_coord(DirectionEject::East);
        assert_eq!(*bot.coord(), (1, 1));

        bot.update_eject_coord(DirectionEject::South);
        assert_eq!(*bot.coord(), (1, 0));

        bot.update_eject_coord(DirectionEject::West);
        assert_eq!(*bot.coord(), (0, 0));
    }

    #[tokio::test]
    async fn test_bot_init() {
        let bot = setup_bot();

        assert_eq!(bot.info().cli_id, 1);
        assert_eq!(bot.info().p_id, 1);
        assert_eq!(bot.info().level, 1);
    }
}
