//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// bot
//

use crate::ai::{AIHandler, AI};
use crate::tcp::command_handle::Direction;

use log::info;

#[derive(Debug, Clone)]
pub struct Bot {
    info: AI,
    coord: (i32, i32),
    backtrack: Vec<(i32, i32)>,
}

impl Bot {
    fn new(info: AI) -> Self {
        Self {
            info,
            coord: (0, 0),
            backtrack: vec![(0, 0)],
        }
    }
}

impl AIHandler for Bot {
    fn init(&mut self, info: AI) -> Self {
        Self::new(info)
    }

    fn update(&mut self) {}
}

impl Bot {
    fn update_coord_movement(&mut self, d: (i32, i32)) {
        let (x, y) = (self.coord.0 + d.0, self.coord.1 + d.1);
        info!("Updating movement of offset: ({}, {})...", d.0, d.1);

        let (width, height) = (self.info.map.0 / 2, self.info.map.1 / 2);

        info!(
            "Coordinated updated from: ({}, {})",
            self.coord.0, self.coord.1
        );

        let wrapped_x = wrap_coordinate(x, width);
        let wrapped_y = wrap_coordinate(y, height);

        info!("To: ({}, {})", wrapped_x, wrapped_y);

        self.coord = (wrapped_x, wrapped_y);
        self.log_path_history(self.coord);
    }

    fn update_eject_coord(&mut self, direction: Direction) {
        info!("Updating movement from Direction: {}...", direction);
        match direction {
            Direction::Center => self.update_coord_movement((0, 0)),
            Direction::North => self.update_coord_movement((0, 1)),
            Direction::NorthWest => self.update_coord_movement((0, 0)),
            Direction::West => self.update_coord_movement((-1, 0)),
            Direction::SouthWest => self.update_coord_movement((0, 0)),
            Direction::South => self.update_coord_movement((0, -1)),
            Direction::SouthEast => self.update_coord_movement((0, 0)),
            Direction::East => self.update_coord_movement((1, 0)),
            Direction::NorthEast => self.update_coord_movement((0, 0)),
        }
    }

    fn log_path_history(&mut self, coord: (i32, i32)) {
        info!("Pushing ({}, {}) to backtrack...", coord.0, coord.1);
        self.backtrack.push(coord);
    }
}

fn wrap_coordinate(coord: i32, max: i32) -> i32 {
    let mut wrapped = (coord % max + max) % max;
    if coord > max {
        wrapped = -(max - (wrapped - 1));
    } else if coord < -max {
        wrapped += 1;
    }
    wrapped
}
