//
// EPITECH PROJECT, 2024
// parsing.rs
// File description:
// paser for config.json
//

#![allow(dead_code)]

use crate::json::{JsonDocument, JsonValue, ParserError};
use std::collections::HashMap;
use std::fmt::Display;
use std::fs;

pub const CONFIG_PATH: &str = "config.json";

#[derive(Debug, Clone, Default, PartialEq)]
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

fn get_number(map: &HashMap<String, JsonValue>, key: &'static str) -> Result<f64, &'static str> {
    match map.get(key).map(|e| match e {
        JsonValue::Number(n) => Ok(n),
        _ => Err("Not a json number for from_lvl"),
    }) {
        Some(e) => e.copied(),
        _ => Err("key not found"),
    }
}

impl Elevation {
    pub fn from_json(obj: JsonValue) -> Result<Elevation, &'static str> {
        let map = match obj {
            JsonValue::Object(map) => map,
            _ => return Err("Not a json object"),
        };

        let from_lvl = get_number(&map, "from_lvl")?;
        let to_lvl = get_number(&map, "to_lvl")?;
        let linemate = get_number(&map, "linemate")?;
        let deraumere = get_number(&map, "deraumere")?;
        let sibur = get_number(&map, "sibur")?;
        let mendiane = get_number(&map, "mendiane")?;
        let phiras = get_number(&map, "phiras")?;
        let thystame = get_number(&map, "thystame")?;

        Ok(Self {
            from_lvl: from_lvl as usize,
            to_lvl: to_lvl as usize,
            linemate: linemate as usize,
            deraumere: deraumere as usize,
            sibur: sibur as usize,
            mendiane: mendiane as usize,
            phiras: phiras as usize,
            thystame: thystame as usize,
        })
    }

    fn set_from_lvl(&mut self, from_lvl: usize) {
        self.from_lvl = from_lvl
    }

    fn set_to_lvl(&mut self, to_lvl: usize) {
        self.to_lvl = to_lvl
    }

    fn set_linemate(&mut self, linemate: usize) {
        self.linemate = linemate
    }

    fn set_deraumere(&mut self, deraumere: usize) {
        self.deraumere = deraumere
    }

    fn set_sibur(&mut self, sibur: usize) {
        self.sibur = sibur
    }

    fn set_mendiane(&mut self, mendiane: usize) {
        self.mendiane = mendiane
    }

    fn set_phiras(&mut self, phiras: usize) {
        self.phiras = phiras
    }

    fn set_thystame(&mut self, thystame: usize) {
        self.thystame = thystame
    }

    pub fn get_from_lvl(self) -> usize {
        self.from_lvl
    }

    pub fn get_to_lvl(self) -> usize {
        self.to_lvl
    }

    pub fn get_linemate_needed(self) -> usize {
        self.linemate
    }

    pub fn get_deraumere_needed(self) -> usize {
        self.deraumere
    }

    pub fn get_sibur_needed(self) -> usize {
        self.sibur
    }

    pub fn get_mendiane_needed(self) -> usize {
        self.mendiane
    }

    pub fn get_phiras_needed(self) -> usize {
        self.phiras
    }

    pub fn get_thystame_needed(self) -> usize {
        self.thystame
    }
}

impl Display for Elevation {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
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
