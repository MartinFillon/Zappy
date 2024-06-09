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
pub struct Inventory {
    food: usize,
    linemate: usize,
    deraumere: usize,
    sibur: usize,
    mendiane: usize,
    phiras: usize,
    thystame: usize,
}

#[derive(Debug, Clone, Default, PartialEq, Bean, Deserialize)]
pub struct Elevation {
    from_lvl: usize,
    to_lvl: usize,
    nb_players: usize,
    inv: Inventory,
}

#[allow(dead_code)]
#[derive(Debug, Deserialize, Default, Bean)]
pub struct Resources {
    name: String,
    density: f32,
}

#[allow(dead_code)]
#[rustfmt::skip]
#[derive(Debug, Deserialize, Default, Bean)]
pub struct Config {
    pub ressources: Vec::<Resources>,
    pub elevation: Vec::<Elevation>,
}

impl Display for Elevation {
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
        write!(
            f,
            "Elevation {{\n  Current level: {},\n  Next level: {},\n  Nb Players needed: {}\n  Linemate needed: {},\n  Deraumere needed: {},\n  Sibur needed: {},\n  Mendiane needed: {},\n  Phiras needed: {},\n  Phiras needed: {}\n}};",
            self.from_lvl,
            self.to_lvl,
            self.nb_players,
            self.inv.linemate,
            self.inv.deraumere,
            self.inv.sibur,
            self.inv.mendiane,
            self.inv.phiras,
            self.inv.thystame,
        )
    }
}
