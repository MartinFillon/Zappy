//
// EPITECH PROJECT, 2024
// parsing.rs
// File description:
// paser for config.json
//

#![allow(dead_code)]

use std::fmt::{self, Display, Formatter};

use zappy_macros::{Bean, Deserialize};

#[derive(Debug, Clone, Default, PartialEq, Bean, Deserialize)]
pub struct Elevation {
    from_lvl: usize,
    to_lvl: usize,
    linemate: usize,
    deraumere: usize,
    sibur: usize,
    mendiane: usize,
    phiras: usize,
    thystame: usize,
}

impl Display for Elevation {
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
        write!(
            f,
            "Elevation {{\n  Current level: {},\n  Next level: {},\n  Linemate needed: {},\n  Deraumere needed: {},\n  Sibur needed: {},\n  Mendiane needed: {},\n  Phiras needed: {},\n  Phiras needed: {}\n}};",
            self.from_lvl,
            self.to_lvl,
            self.linemate,
            self.deraumere,
            self.sibur,
            self.mendiane,
            self.phiras,
            self.thystame,
        )
    }
}
