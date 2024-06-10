//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// knight
//

use crate::ai::{utils, AIHandler, AI};
use crate::commands;
use crate::move_towards_broadcast::backtrack_eject;
use crate::tcp::command_handle::{CommandError, Direction, ResponseResult};
use crate::tcp::TcpClient;

use async_trait::async_trait;

use log::info;

#[derive(Debug, Clone)]
pub struct Knight {
    info: AI,
    coord: (i32, i32),
    backtrack: Vec<(i32, i32)>,
}

impl Knight {
    fn new(info: AI) -> Self {
        Self {
            info,
            coord: (0, 0),
            backtrack: vec![(0, 0)],
        }
    }
}

#[async_trait]
impl AIHandler for Knight {
    fn init(info: AI) -> Self {
        Self::new(info)
    }

    async fn update(&mut self) -> Result<(), CommandError> {
        let mut _client_lock = self.info.client.lock().await;

        Ok(())
    }
}

impl Knight {
    fn update_coord_movement(&mut self, d: (i32, i32)) {
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

        self.coord = (wrapped_x, wrapped_y);
        self.log_path_history(self.coord);
    }

    fn update_eject_coord(&mut self, direction: Direction) {
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

    fn log_path_history(&mut self, coord: (i32, i32)) {
        info!("Pushing ({}, {}) to backtrack...", coord.0, coord.1);
        self.backtrack.push(coord);
    }

    async fn handle_reject(
        &mut self,
        client: &mut TcpClient,
        res: Result<ResponseResult, CommandError>,
    ) -> Result<ResponseResult, CommandError> {
        if let Ok(ResponseResult::Eject(ref dir)) = res {
            if backtrack_eject(client, dir.clone()).await {
                // to finish backtrack_eject then
                self.update_eject_coord(dir.clone());
                return Ok(ResponseResult::OK);
            }
        }
        res
    }
}
