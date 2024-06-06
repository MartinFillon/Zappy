//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// bot
//

use crate::ai::{AIHandler, AI};
use crate::tcp::command_handle::Direction;

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
        let x = self.coord.0 + d.0;
        let y = self.coord.1 + d.1;
        let width = self.info.map.0;
        let height = self.info.map.1;

        let wrapped_x = (x % width + width) % width;
        let wrapped_y = (y % height + height) % height;

        self.coord = (wrapped_x, wrapped_y);
        self.log_path_history(self.coord);
    }

    fn update_eject_coord(&mut self, direction: Direction) {
        match direction {
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
        self.backtrack.push(coord);
    }
}
