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
        incantation::{handle_incantation, incantation, wait_for_incantation},
        inventory::inventory,
        look_around::look_around,
        move_up::move_up,
        take_object::take_object,
    },
    elevation::{Config, Inventory},
    move_towards_broadcast::{backtrack_eject, move_towards_broadcast, turn_towards_broadcast},
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
const QUEENS_IDS: [usize; 4] = [2, 1, 4, 3];

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

    // async fn update(&mut self) -> Result<(), CommandError> {
    //     {
    //         let mut client = self.info().client().lock().await;
    //         if let Err(CommandError::DeadReceived) = client.get_broadcast().await {
    //             return Err(CommandError::DeadReceived);
    //         }
    //     }
    //     if let Err(CommandError::DeadReceived) = self.handle_message().await {
    //         return Err(CommandError::DeadReceived);
    //     }
    //     if let Err(CommandError::DeadReceived) = self.fork_servants().await {
    //         return Err(CommandError::DeadReceived);
    //     }
    //     loop {
    //         if let Err(CommandError::DeadReceived) = self.handle_message().await {
    //             break;
    //         }
    //         if let Err(CommandError::DeadReceived) = self.check_move_elevation().await {
    //             break;
    //         }

    //         let look_res = {
    //             let mut cli = self.info.client.lock().await;
    //             println!("Queen {} calling Look...", self.info.p_id);
    //             let res = look_around::look_around(&mut cli).await;
    //             println!("Queen {} Look returned: {:?}", self.info.p_id, res);
    //             Queen::queen_checkout_response(&mut cli, res).await
    //         };
    //         if let Ok(ResponseResult::Tiles(vec)) = look_res {
    //             self.convert_to_look_info(vec[0].clone());
    //         }

    //         let inventory_res = {
    //             let mut cli = self.info.client.lock().await;
    //             println!("Queen {} calling Inventory...", self.info.p_id);
    //             let res = inventory::inventory(&mut cli).await;
    //             println!("Queen {} Inventory returned: {:?}", self.info.p_id, res);
    //             Queen::queen_checkout_response(&mut cli, res).await
    //         };
    //         if let Ok(ResponseResult::Inventory(vec)) = inventory_res {
    //             self.convert_to_inv(vec);
    //         }

    //         if let Err(CommandError::DeadReceived) = self.check_enough_food(40).await {
    //             break;
    //         }

    //         if let Err(CommandError::DeadReceived) = self.create_bot().await {
    //             break;
    //         }

    //         if self.check_requirement() {
    //             println!("Ai Queen #{} is incantating", self.info.p_id);
    //             if let Err(e) = self.incantate().await {
    //                 warn!("Error from incantation: {}", e);
    //                 println!("Error with Queen #{} incantating.", self.info.p_id);
    //                 if e == CommandError::DeadReceived || e == CommandError::RequestError {
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    //     Err(CommandError::DeadReceived)
    // }

    async fn update(&mut self) -> Result<(), CommandError> {
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
            if info.slots == 0 && info.cli_id < 3 {
                Queen::spawn_queen(info.clone(), info.cli_id, &mut client).await?;
                info!("[{}] Spawned queen.", info.cli_id);
            }
            if info.slots >= 0 && info.cli_id > 3 {
                info!("[{}] Identified as NPC.", info.cli_id);
                Queen::connect_leftovers(info.clone()).await?;
            }
            info!("[{}] Unblocked.", info.cli_id);
        }
        self.info.set_p_id(self.info().cli_id);
        println!(
            "[{}] Queen is now certified and verified.",
            self.info.cli_id
        );

        self.handle_message().await?;
        self.fork_servants().await?;

        loop {
            self.handle_message().await?;
            self.check_move_elevation().await?;

            let look_res = {
                let mut cli = self.info.client.lock().await;
                let res = look_around(&mut cli).await;
                Queen::handle_eject(&mut cli, res).await
            };
            if let Ok(ResponseResult::Tiles(vec)) = look_res {
                self.convert_to_look_info(vec[0].clone());
            }

            let inventory_res = {
                let mut cli = self.info.client.lock().await;
                let res = inventory(&mut cli).await;
                Queen::handle_eject(&mut cli, res).await
            };
            if let Ok(ResponseResult::Inventory(vec)) = inventory_res {
                self.convert_to_inv(vec);
            }

            self.check_enough_food(8).await?;

            if self.check_requirement() {
                println!(
                    "[{}] Ai Queen #{} is incantating",
                    self.info.cli_id, self.info.p_id
                );
                if let Err(e) = self.incantate().await {
                    warn!("[{}] Error from incantation: {}", self.info.cli_id, e);
                    println!(
                        "[{}] Error with Queen #{} incantating.",
                        self.info.cli_id, self.info.p_id
                    );
                }
            }
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
                let response = client.check_response().await;
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
        self.analyse_messages().await
    }
}

impl Queen {
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

        move_up(client).await?;
        fork(client).await?;
        inventory(client).await?;
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
    /// Move [`Queen`] at level 4,
    /// we assume that all the queens have the same direction
    ///
    async fn move_queen_first_step(&mut self) -> Result<(), CommandError> {
        println!("Queen {} handling can move.", self.info.p_id);
        if self.info.p_id == 2 || self.info.p_id == 4 {
            println!(
                "Queen {} level {} broadcasting...",
                self.info.p_id, self.info.level
            );
            {
                let mut client = self.info().client().lock().await;
                broadcast(
                    &mut client,
                    format!("{} waiting", self.info().p_id).as_str(),
                )
                .await?;
            }
            println!(
                "Queen {} level {} broadcast \"waiting\".",
                self.info.p_id, self.info.level
            );
            self.set_can_move(false);
            self.set_moved_lvl4(true);
            return Ok(());
        } else if self.partner_dir.is_some() {
            {
                let mut client = self.info().client().lock().await;
                move_towards_broadcast(
                    &mut client,
                    self.partner_dir.clone().unwrap_or(DirectionMessage::Center),
                )
                .await?;
                broadcast(&mut client, format!("{} mv", self.info().p_id).as_str()).await?;
                println!("Queen {} level {} moved!", self.info.p_id, self.info.level);
            }
            self.set_can_move(false);
            self.set_partner_dir(None);
        } else {
            println!(
                "Queen {} level {} trying to receive broadcast \"waiting\".",
                self.info.p_id, self.info.level
            );
            self.analyse_messages().await?;
        }
        //{
        //    let mut cli = self.info.client.lock().await;
        //    move_up::move_up(&mut cli).await?;
        //    let broad_res =
        //        broadcast::broadcast(&mut cli, format!("{} mv", self.info.p_id).as_str())
        //            .await?;
        //    Queen::queen_checkout_response(&mut cli, Ok(broad_res)).await?;
        //}
        Ok(())
    }

    ///
    /// Move [`Queen`] at level 6, we will move queen's direction and then reunite them in a single tile
    ///
    async fn move_queen_second_step(&mut self) -> Result<(), CommandError> {
        {
            let mut client = self.info().client().lock().await;
            broadcast(
                &mut client,
                format!("{} waiting", self.info().p_id).as_str(),
            )
            .await?;
        }
        self.analyse_messages().await?;
        Ok(())
    }

    async fn check_move_elevation(&mut self) -> Result<(), CommandError> {
        if !self.can_move() {
            return Ok(());
        }
        match self.info.level {
            4 => self.move_queen_first_step().await,
            6 => self.move_queen_second_step().await,
            _ => Ok(()),
        }
    }

    async fn incantate(&mut self) -> Result<(), CommandError> {
        let mut level = self.info().level;
        {
            let mut cli = self.info.client.lock().await;
            broadcast(&mut cli, format!("{} inc", self.info().p_id).as_str()).await?;
            println!(
                "[{}] Ai Queen #{} launching incantation",
                self.info.cli_id, self.info.p_id
            );
            let incant_res = incantation(&mut cli).await;
            println!(
                "[{}] Ai Queen #{} done incantating.",
                self.info.cli_id, self.info.p_id
            );
            println!(
                "Queen {} Incantation result: {:?}",
                self.info.p_id, incant_res
            );
            if let Ok(ResponseResult::Incantation(lvl)) =
                self.queen_checkout_response(&mut cli, incant_res).await
            {
                level = lvl;
                println!("Queen {} done. Now level {}", self.info.p_id, level);
                if level == 4 || level == 6 {
                    error!(
                        "[{}] Queen {} lvl {}",
                        self.info.cli_id, self.info.p_id, level
                    );
                    broadcast(
                        &mut cli,
                        format!("{} lvl {}", self.info().p_id, level).as_str(),
                    )
                    .await?;
                }
            }
            if level == 4 || level == 6 {
                error!(
                    "[{}] Queen {} lvl {}",
                    self.info.cli_id, self.info.p_id, level
                );
                broadcast(
                    &mut cli,
                    format!("{} lvl {}", self.info().p_id, level).as_str(),
                )
                .await?;
            }
        }
        self.info.set_level(level);
        Ok(())
    }

    async fn check_enough_food(&mut self, min: usize) -> Result<(), CommandError> {
        while *self.inv.food() < min {
            let mut cli = self.info.client.lock().await;
            if let Ok(ResponseResult::OK) = take_object(&mut cli, "food").await {
                self.inv.set_food(self.inv.food() + 1);
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

        for _ in 0..NB_INIT_BOTS {
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
        }
        info!("[{}] Miserable peasants... SERVE ME.\n", self.info.cli_id);

        Ok(())
    }

    fn check_requirement(&self) -> bool {
        let idx = self.info.level - 1;
        let require = &self.requirement.elevation[idx];
        let r_inv = require.inv();
        let look = &self.look;

        if self.info().level >= 4
            && self.moved_lvl4
            && (self.info().p_id == 1 || self.info().p_id == 3)
        {
            return false;
        }
        if self.info().level >= 6 && self.moved_lvl6 && (self.info().p_id == 2) {
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

    fn convert_to_look_info(&mut self, vec: Vec<String>) {
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
    }

    ///
    /// Transform Inventory info to exploit them later.
    ///
    fn convert_to_inv(&mut self, vec: Vec<(String, i32)>) {
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
    }

    fn is_paired_queen(&self, id: usize, lvl: i32) -> bool {
        error!("[{}] id = {}, level = {}, pid = {}", self.info.cli_id, id, lvl, self.info().p_id);
        (lvl == 4 && id == QUEENS_IDS[self.info().p_id - 1])
            || (lvl == 6
                && ((id == 1 | 2 && self.info().p_id == 3 | 4)
                    || (id == 3 | 4 && self.info().p_id == 1 | 2)))
    }

    async fn handle_message_content(
        &self,
        client: &mut TcpClient,
        id: usize,
        (dir, msg): (DirectionMessage, &str),
        can_move: &mut bool,
        level: &mut usize,
        save_dir: &mut Option<DirectionMessage>,
    ) -> Result<ResponseResult, CommandError> {
        match msg {
            level if level.starts_with("lvl ") => {
                if let Ok(lvl) = msg.split_at(3).1.trim_start().parse::<i32>() {
                    if self.is_paired_queen(id, lvl) {
                        *can_move = true;
                        println!(
                            "[{}] Queen {} can now move towards Queen {}!",
                            self.info.cli_id,
                            self.info.p_id, id
                        );
                    }
                }
            }
            "Done" => {
                turn_towards_broadcast(client, dir.clone()).await?;
            }
            "waiting" => {
                if self.is_paired_queen(id, self.info().level as i32) {
                    if (self.info().level == 4 && self.moved_lvl4)
                        || (self.info().level == 6 && self.moved_lvl6)
                    {
                        println!(
                            "Queen {} level {} already moved.",
                            self.info.p_id, self.info.level
                        );
                        return Ok(ResponseResult::OK);
                    }
                    if self.info().level == 4 && (self.info().p_id == 2 || self.info().p_id == 4) {
                        println!("Queen {} is already waiting.", self.info.p_id);
                        return Ok(ResponseResult::OK);
                    }
                    if !self.can_move
                        && ((self.info.p_id == 1 && id == 2) || (self.info.p_id == 3 && id == 4))
                    {
                        *save_dir = Some(dir.clone());
                        return Ok(ResponseResult::OK);
                    }
                    move_towards_broadcast(client, dir).await?;
                    broadcast(client, format!("{} mv", self.info().p_id).as_str()).await?;
                    println!("Queen {} level {} moved!", self.info.p_id, self.info.level);
                    *can_move = false;
                }
            }
            "inc" => {
                if (self.info.level == 4 || self.info.level == 5)
                    && self.moved_lvl4
                    && ((self.info.p_id == 1 && id == 2) || (self.info.p_id == 3 && id == 4))
                {
                    if let ResponseResult::Incantation(lvl) = wait_for_incantation(client).await? {
                        *level = lvl;
                    }
                }
                if (self.info.level == 6 || self.info.level == 7)
                    && self.moved_lvl6
                    && ((self.info.p_id >= 1 && self.info.p_id <= 3) && id == 4)
                {
                    if let ResponseResult::Incantation(lvl) = wait_for_incantation(client).await? {
                        *level = lvl;
                    }
                }
            }
            _ => {}
        }
        Ok(ResponseResult::OK)
    }

    async fn analyse_messages(&mut self) -> Result<ResponseResult, CommandError> {
        let mut can_move = self.can_move;
        let mut level = self.info().level;
        let mut save_dir: Option<DirectionMessage> = None;
        {
            let mut client = self.info.client.lock().await;
            while let Some((dir, msg)) = client.pop_message() {
                info!("Queen {}: handling message: {}", self.info().p_id, msg);
                let content = if let Some(idex) = msg.trim_end_matches('\n').find(' ') {
                    msg.split_at(idex)
                } else {
                    ("0", msg.trim_end_matches('\n'))
                };
                if let Ok(id) = content.0.parse::<usize>() {
                    self.handle_message_content(
                        &mut client,
                        id,
                        (dir.clone(), content.1.trim_start()),
                        &mut can_move,
                        &mut level,
                        &mut save_dir,
                    )
                    .await?;
                }
            }
        }
        if self.can_move && !can_move {
            if self.info().level == 4 {
                println!("Queen {} set moved lvl 4 to true.", self.info.p_id);
                self.set_moved_lvl4(true);
            }
            if self.info().level == 6 {
                println!("Queen {} set moved lvl 6 to true.", self.info.p_id);
                self.set_moved_lvl6(true);
            }
        }
        if save_dir.is_some() {
            self.set_partner_dir(save_dir);
        }
        self.info.set_level(level);
        self.set_can_move(can_move);
        Ok(ResponseResult::OK)
    }

    async fn create_bot(&mut self) -> Result<ResponseResult, CommandError> {
        let mut client = self.info().client().lock().await;
        let res = fork(&mut client).await;
        if let Ok(ResponseResult::OK) = self.queen_checkout_response(&mut client, res).await {
            let info = self.info.clone();
            tokio::spawn(async move {
                if let Err(err) = fork_ai(info.clone()).await {
                    error!("[{}] AI fork error: {}", info.cli_id, err);
                } else {
                    println!("[{}] AI successfully forked.", info.cli_id);
                }
            });
            broadcast(
                &mut client,
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
mod test_queen {

}