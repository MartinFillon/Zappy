//
// EPITECH PROJECT, 2024
// parsing.rs
// File description:
// paser for config.json
//

#![allow(dead_code)]

use crate::json::{JsonDocument, JsonValue};
use rust_macros::Bean;
use std::collections::HashMap;
use std::fmt::Display;
use std::fs;

pub const CONFIG_PATH: &str = "config.json";

#[derive(Debug, Clone, Default, PartialEq, Bean)]
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

fn get_number(map: &HashMap<String, JsonValue>, key: &str) -> Result<f64, String> {
    match map.get(key).map(|e| match e {
        JsonValue::Number(n) => Ok(n),
        _ => Err(String::from("Not a json number for from_lvl")),
    }) {
        Some(e) => e.copied(),
        _ => Err(String::from("Key not found")),
    }
}

impl Elevation {
    pub fn from_json(obj: JsonValue) -> Result<Elevation, String> {
        let map = match obj {
            JsonValue::Object(map) => map,
            _ => return Err(String::from("Not a json object")),
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

    fn get_elevation_infos(map: &HashMap<String, JsonValue>) -> Result<Vec<Elevation>, String> {
        match map.get("elevation") {
            Some(JsonValue::Array(values)) => {
                let mut list: Vec<Elevation> = vec![];
                for obj in values {
                    list.push(Self::from_json(obj.clone())?);
                }
                Ok(list)
            }
            Some(_) => Err(String::from("Expected array of values")),
            None => Err(String::from("Couldn't find \"elevation\" part in file")),
        }
    }

    pub fn from_conf(filepath: &str) -> Result<Vec<Elevation>, String> {
        match fs::read_to_string(filepath).map(|content| {
            match JsonDocument::try_from(content.as_ref()) {
                Ok(JsonDocument(JsonValue::Object(map))) => Self::get_elevation_infos(&map),
                Ok(_) => Err(String::from("Expected object \"elevation\"")),
                Err(e) => Err(e.to_string()),
            }
        }) {
            Ok(e) => e,
            Err(e) => Err(e.to_string()),
        }
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
