//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// queen
//

use crate::{
    ai::{fork_ai, AIHandler, Incantationers, AI},
    commands::{
        broadcast::broadcast,
        fork::fork,
        incantation::{handle_incantation, incantation},
        inventory::inventory,
        look_around::look_around,
        take_object::take_object,
        turn::{turn, DirectionTurn},
    },
    elevation::{Config, Inventory},
    move_towards_broadcast::{backtrack_eject, move_towards_broadcast},
    tcp::{
        command_handle::{CommandError, CommandHandler, DirectionMessage, ResponseResult},
        TcpClient,
    },
};

use core::fmt;
use std::fmt::{Display, Formatter};

use async_trait::async_trait;

#[allow(unused_imports)]
use log::{debug, error, info, warn};

use zappy_macros::Bean;

use super::Listeners;

const NB_INIT_BOTS: usize = 2;
const NB_INIT_QUEENS: usize = 8;
const QUEENS_IDS: [usize; 4] = [1, 0, 3, 2];

#[derive(Debug, Clone, Default)]
struct LookInfo {
    nb_player: usize,
    inv: Inventory,
}

#[derive(Debug, Clone, Bean)]
pub struct Queen {
    pub info: AI,
    inv: Inventory,
    look: LookInfo,
    requirement: Config,
    can_move: bool,
    moved_lvl4: bool,
    moved_lvl6: bool,
    partner_dir: Option<DirectionMessage>,
}

#[async_trait]
impl AIHandler for Queen {
    fn init(info: AI) -> Self {
        println!("[{}] Queen has arrived. (default)", info.cli_id);
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        self.start_queen().await?;
        self.join_queens().await?;
        self.fork_servants().await?;

        println!(
            "[{}] Queen {} ready to go!",
            self.info.cli_id, self.info.p_id
        );

        while self.info.level < 8 {
            self.get_look_infos().await?;
            self.get_inv_infos().await?;

            self.check_enough_food(30).await?;

            if self.check_requirement() {
                self.incantate().await?;
            }
        }
        error!(
            "[{}] Queen {} lvl {}",
            self.info.cli_id, self.info.p_id, self.info.level
        );
        loop {
            self.check_enough_food(30).await?;
        }
    }
}

#[async_trait]
impl Incantationers for Queen {
    async fn handle_eject(
        client: &mut TcpClient,
        res: Result<ResponseResult, CommandError>,
    ) -> Result<ResponseResult, CommandError> {
        if let Ok(ResponseResult::Eject(ref dir)) = res {
            if backtrack_eject(client, dir.clone()).await {
                let response = client
                    .check_response()
                    .await
                    .ok_or(CommandError::NoResponseReceived)?;
                client.handle_response(response).await?;
            }
        }
        res
    }

    async fn handle_elevating(
        &self,
        client: &mut TcpClient,
        res: Result<ResponseResult, CommandError>,
    ) -> Result<ResponseResult, CommandError> {
        if let Ok(ResponseResult::Elevating) = res {
            handle_incantation(client).await
        } else {
            res
        }
    }
}

#[async_trait]
impl Listeners for Queen {
    async fn handle_message(&mut self) -> Result<ResponseResult, CommandError> {
        Ok(ResponseResult::OK)
    }
}

impl Queen {
    ///
    /// Meant to initialize the connected Queen, if there is no more room for players, new Queens are forked.
    /// If there is too many room for players, Queen just dies to get rid of leftover eggs.
    ///
    async fn start_queen(&mut self) -> Result<(), CommandError> {
        {
            let mut client = self.info().client().lock().await;
            let info = self.info().clone();
            info!(
                "[{}] Blocking, checking requirements of all queens...",
                info.cli_id
            );
            debug!(
                "[{}] Unused slot checked: {} | Number of queens created: {}",
                info.cli_id,
                info.slots,
                info.cli_id + 1
            );
            if info.slots == 0 && info.cli_id < NB_INIT_QUEENS - 1 {
                Queen::spawn_queen(info.clone(), info.cli_id, &mut client).await?;
                info!("[{}] Spawned queen.", info.cli_id);
            }
            if info.slots >= 0 && info.cli_id > NB_INIT_QUEENS - 1 {
                info!("[{}] Identified as NPC.", info.cli_id);
                Queen::connect_leftovers(info.clone()).await?;
            }
            info!("[{}] Unblocked.", info.cli_id);
        }
        self.info.set_p_id(self.info().cli_id);
        println!(
            "[{}] Queen {} is now certified and verified.",
            self.info.cli_id, self.info.p_id
        );
        Ok(())
    }

    ///
    /// All Queens move towards first Queen logged in (p_id 0).
    ///
    /// First Queen logged in just broadcasts.
    ///
    async fn join_queens(&mut self) -> Result<(), CommandError> {
        if self.info.p_id == 0 {
            let mut client = self.info.client.lock().await;
            broadcast(&mut client, format!("{} waiting", self.info.p_id).as_str()).await?;
        } else {
            let mut client = self.info.client.lock().await;
            println!(
                "[{}] Queen {} moving towards Queen 0.",
                self.info.cli_id, self.info.p_id
            );
            loop {
                if let ResponseResult::Message((dir, msg)) = client.get_broadcast().await? {
                    if dir == DirectionMessage::Center && msg.contains('0') {
                        break;
                    }
                    move_towards_broadcast(&mut client, dir.clone()).await?;
                }
            }
        }
        Ok(())
    }

    /// Checks for an "eject" of "Elevation underway" response
    async fn queen_checkout_response(
        &self,
        client: &mut TcpClient,
        res: Result<ResponseResult, CommandError>,
    ) -> Result<ResponseResult, CommandError> {
        match res {
            Ok(ResponseResult::Eject(_)) => Queen::handle_eject(client, res).await,
            Ok(ResponseResult::Elevating) => self.handle_elevating(client, res).await,
            _ => res,
        }
    }

    /// Creates a new [`Queen`].
    fn new(info: AI) -> Self {
        Self {
            info,
            inv: Default::default(),
            look: Default::default(),
            requirement: zappy_json::create_from_file::<Config>("config.json").unwrap(),
            can_move: false,
            moved_lvl4: false,
            moved_lvl6: false,
            partner_dir: None,
        }
    }

    ///
    /// Spawns a new [`Queen`] from `id` to `id + 1`.
    ///
    /// * `id` - the id that is spawning the `Queen`, furthermore, this will give the new queen the `cli_id` and `p_id` of `id + 1`
    async fn spawn_queen(info: AI, id: usize, client: &mut TcpClient) -> Result<(), CommandError> {
        let info_clone = info.clone();

        fork(client).await?;
        turn(client, DirectionTurn::Left).await?;
        tokio::spawn(async move {
            if let Err(err) = fork_ai(info_clone).await {
                error!("[{}] AI executing task fork error: {}", info.cli_id, err);
            } else {
                println!("[{}] AI successfully forked task.", info.cli_id);
            }
        });
        broadcast(
            client,
            format!("{} assign Queen {}", info.cli_id, id + 1).as_str(),
        )
        .await?;
        Ok(())
    }

    ///
    /// Connects a new [`Bot`] client from `id`.
    ///
    /// * `id` - the id that is spawning the `Bot`, furthermore, this will give the new bot the preceeding `cli_id` and `p_id` of `0`
    async fn connect_leftovers(info: AI) -> Result<(), CommandError> {
        let mut client = info.client().lock().await;
        while let Some(response) = client.get_response().await {
            if response.trim_end() == "dead" {
                println!(
                    "[{}] AI : NPC at connection died from natural causes.",
                    info.cli_id
                );
                return Err(CommandError::DeadReceived);
            }
        }
        Ok(())
    }

    ///
    /// Launches Queen's incantation process to level up
    ///
    async fn incantate(&mut self) -> Result<(), CommandError> {
        let mut level = self.info().level;
        {
            let mut cli = self.info.client.lock().await;
            println!(
                "[{}] Queen {} launching incantation",
                self.info.cli_id, self.info.p_id
            );
            let incant_res = incantation(&mut cli).await?;
            println!(
                "[{}] Queen {} done incantating.",
                self.info.cli_id, self.info.p_id
            );
            if let Ok(ResponseResult::Incantation(lvl)) =
                self.queen_checkout_response(&mut cli, Ok(incant_res)).await
            {
                level = lvl;
                println!(
                    "[{}] Queen {} done. Now level {}",
                    self.info.cli_id, self.info.p_id, level
                );
                if level == 4 || level == 6 {
                    info!(
                        "[{}] Queen {} lvl {}",
                        self.info.cli_id, self.info.p_id, level
                    );
                }
                self.create_bot(&mut cli).await?;
            }
        }
        self.info.set_level(level);
        Ok(())
    }

    ///
    /// Checks if Queen has enough food compared to `min`
    ///
    /// If the amount held is lower than `min`, she picks up food
    ///
    async fn check_enough_food(&mut self, min: usize) -> Result<(), CommandError> {
        while *self.inv.food() < min {
            let res = {
                let mut cli = self.info.client.lock().await;
                let res = take_object(&mut cli, "food").await;
                self.queen_checkout_response(&mut cli, res).await?
            };
            match res {
                ResponseResult::OK => self.inv.set_food(self.inv.food() + 1),
                ResponseResult::Incantation(lvl) => {
                    self.info.set_level(lvl);
                    if self.info.level == 4 || self.info.level == 6 {
                        error!(
                            "[{}] Queen {} lvl {}",
                            self.info.cli_id, self.info.p_id, self.info.level
                        );
                    }
                    println!(
                        "[{}] Queen {} done. Now level {}",
                        self.info.cli_id, self.info.p_id, self.info.level
                    );
                }
                _ => {}
            }
        }
        Ok(())
    }

    async fn fork_servants(&mut self) -> Result<(), CommandError> {
        let mut cli = self.info.client.lock().await;

        fork(&mut cli).await?;
        let info = self.info.clone();
        tokio::spawn(async move {
            if let Err(err) = fork_ai(info.clone()).await {
                error!("[{}] AI fork error: {}", info.cli_id, err);
            } else {
                println!("[{}] AI successfully forked.", info.cli_id);
            }
        });
        broadcast(
            &mut cli,
            format!("{} assign Knight {}", self.info().cli_id, self.info().p_id).as_str(),
        )
        .await?;
        println!(
            "[{}] I as the queen ({}), bestow my life uppon you",
            self.info.cli_id, self.info.p_id
        );

        fork(&mut cli).await?;
        let info = self.info.clone();
        tokio::spawn(async move {
            if let Err(err) = fork_ai(info.clone()).await {
                error!("[{}] AI fork error: {}", info.cli_id, err);
            } else {
                println!("[{}] AI successfully forked.", info.cli_id);
            }
        });
        broadcast(
            &mut cli,
            format!("{} assign Bot {}", self.info().cli_id, self.info().p_id).as_str(),
        )
        .await?;

        Ok(())
    }

    ///
    /// Checks if Queen can level up based on `self.look` and `self.inv` infos
    ///
    fn check_requirement(&self) -> bool {
        let idx = if self.info.level == 8 {
            0
        } else {
            self.info.level - 1
        };
        let require = &self.requirement.elevation[idx];
        let r_inv = require.inv();
        let look = &self.look;

        if self.info.level >= 4 && self.info.p_id % 3 != 0 {
            return false;
        }
        if self.info.level >= 6 && self.info.p_id % 6 != 0 {
            return false;
        }

        look.nb_player >= *require.nb_players()
            && look.inv.food() >= r_inv.food()
            && look.inv.linemate() >= r_inv.linemate()
            && look.inv.deraumere() >= r_inv.deraumere()
            && look.inv.sibur() >= r_inv.sibur()
            && look.inv.mendiane() >= r_inv.mendiane()
            && look.inv.phiras() >= r_inv.phiras()
            && look.inv.thystame() >= r_inv.thystame()
    }

    ///
    /// Transform Look info to exploit them later
    ///
    async fn get_look_infos(&mut self) -> Result<(), CommandError> {
        let res = {
            let mut cli = self.info.client.lock().await;
            let res = look_around(&mut cli).await;
            self.queen_checkout_response(&mut cli, res).await?
        };
        let vec = match &res {
            ResponseResult::Incantation(lvl) => {
                self.info.set_level(*lvl);
                if self.info.level == 4 || self.info.level == 6 {
                    warn!(
                        "[{}] Queen {} lvl {}",
                        self.info.cli_id, self.info.p_id, self.info.level
                    );
                }
                println!(
                    "[{}] Queen {} done. Now level {}",
                    self.info.cli_id, self.info.p_id, self.info.level
                );
                return Ok(());
            }
            ResponseResult::Tiles(tiles) => {
                if tiles.is_empty() {
                    return Ok(());
                }
                tiles[0].clone()
            }
            _ => return Ok(()),
        };

        self.look.inv.clear();

        let inv: &mut Inventory = &mut self.look.inv;

        for elem in vec.iter() {
            match elem.as_str() {
                "player" => self.look.nb_player += 1,
                "food" => inv.set_food(inv.food() + 1),
                "linemate" => inv.set_linemate(inv.linemate() + 1),
                "deraumere" => inv.set_deraumere(inv.deraumere() + 1),
                "sibur" => inv.set_sibur(inv.sibur() + 1),
                "mendiane" => inv.set_mendiane(inv.mendiane() + 1),
                "phiras" => inv.set_phiras(inv.phiras() + 1),
                "thystame" => inv.set_thystame(inv.thystame() + 1),
                _ => (),
            }
        }
        Ok(())
    }

    ///
    /// Transform Inventory info to exploit them later.
    ///
    async fn get_inv_infos(&mut self) -> Result<(), CommandError> {
        let res = {
            let mut cli = self.info.client.lock().await;
            let res = inventory(&mut cli).await?;
            self.queen_checkout_response(&mut cli, Ok(res)).await?
        };
        let vec: Vec<(String, i32)> = match &res {
            ResponseResult::Incantation(lvl) => {
                self.info.set_level(*lvl);
                if self.info.level == 4 || self.info.level == 6 {
                    error!(
                        "[{}] Queen {} lvl {}",
                        self.info.cli_id, self.info.p_id, self.info.level
                    );
                }
                println!(
                    "[{}] Queen {} done. Now level {}",
                    self.info.cli_id, self.info.p_id, self.info.level
                );
                return Ok(());
            }
            ResponseResult::Inventory(inv) => {
                if inv.is_empty() {
                    return Ok(());
                }
                inv.clone()
            }
            _ => return Ok(()),
        };

        for elem in vec.iter() {
            match elem.0.as_str() {
                "food" => self.inv.set_food(elem.1 as usize),
                "linemate" => self.inv.set_linemate(elem.1 as usize),
                "deraumere" => self.inv.set_deraumere(elem.1 as usize),
                "sibur" => self.inv.set_sibur(elem.1 as usize),
                "mendiane" => self.inv.set_mendiane(elem.1 as usize),
                "phiras" => self.inv.set_phiras(elem.1 as usize),
                "thystame" => self.inv.set_thystame(elem.1 as usize),
                _ => (),
            }
        }
        Ok(())
    }

    async fn create_bot(&self, client: &mut TcpClient) -> Result<ResponseResult, CommandError> {
        let res = fork(client).await?;
        if let Ok(ResponseResult::OK) = self.queen_checkout_response(client, Ok(res)).await {
            let info = self.info.clone();
            tokio::spawn(async move {
                if let Err(err) = fork_ai(info.clone()).await {
                    error!("[{}] AI fork error: {}", info.cli_id, err);
                } else {
                    println!("[{}] AI successfully forked.", info.cli_id);
                }
            });
            broadcast(
                client,
                format!("{} assign Bot {}", self.info().cli_id, self.info().p_id).as_str(),
            )
            .await?;
        }
        Ok(ResponseResult::OK)
    }
}

impl Display for Queen {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "Queen => {}", self.info)
    }
}

#[cfg(test)]
mod queen_test {
    use super::*;
    use crate::ai::AI;
    use crate::tcp::TcpClient;

    use std::sync::Arc;
    use tokio::sync::Mutex;

    fn setup_queen() -> Queen {
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
        Queen::new(ai)
    }
}
