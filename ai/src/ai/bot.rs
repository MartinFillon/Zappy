//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// bot
//

use crate::ai::{AIHandler, Action, AI};
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

    fn update(&mut self, action: Option<Action>) {}
}

impl Bot {
    fn update_coord_movement(&mut self, offset_coord: (i32, i32)) {
        let x = self.coord.0 - offset_coord.0;
        let y = self.coord.1 - offset_coord.1;
        self.coord = (x, y);
        self.log_path_history(self.coord);
    }

    fn update_eject_coord(&mut self, direction: Direction) {
        match direction {
            Direction::North => self.coord = (self.coord.0, (self.coord.1 + 1)),
            Direction::NorthWest => self.coord = ((self.coord.0 - 1), (self.coord.1 + 1)),
            Direction::West => self.coord = (self.coord.0 - 1, self.coord.1),
            Direction::SouthWest => self.coord = ((self.coord.0 - 1), (self.coord.1 - 1)),
            Direction::South => self.coord = (self.coord.0, (self.coord.1 - 1)),
            Direction::SouthEast => self.coord = ((self.coord.0 + 1), (self.coord.1 - 1)),
            Direction::East => self.coord = ((self.coord.0 + 1), self.coord.1),
            Direction::NorthEast => self.coord = ((self.coord.0 + 1), (self.coord.1 + 1)),
        }
        self.log_path_history(self.coord);
    }

    fn log_path_history(&mut self, coord: (i32, i32)) {
        self.backtrack.push(coord);
    }
}
