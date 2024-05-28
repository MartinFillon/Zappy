#![allow(dead_code)]

use std::collections::HashMap;

use serde::Deserialize;

use crate::{connection::Connection, server::ServerOptions};

#[derive(Debug, Deserialize)]
pub enum Mode {
    GRAPHIC,    // "GRAPHIC"
    AI(String), // {"AI": "team_name"}
}

#[derive(Debug)]
struct Position {
    x: u32,
    y: u32,
}

#[derive(Debug)]
pub struct Ai {
    position: Position,
    level: u32,
    inventory: HashMap<String, u32>,
}

#[derive(Debug, Default)]
pub struct Graphic {
    map_size: (u32, u32),
    teams: Vec<String>,
    eggs: HashMap<u32, Position>,
    players: HashMap<u32, Ai>,
}

pub trait Client {
    fn connect(
        &mut self,
        sock: &mut Connection,
        server_options: &ServerOptions,
    ) -> Result<(), String>;
}

impl Client for Graphic {
    fn connect(
        &mut self,
        sock: &mut Connection,
        server_options: &ServerOptions,
    ) -> Result<(), String> {
        sock.send("GRAPHIC".to_string())
            .map_err(|e| e.to_string())?;

        let mp_size = sock.get_line().map_err(|e| e.to_string())?;

        dbg!(&mp_size);

        let mp_size_trimmed = mp_size
            .trim_end()
            .split(' ')
            .map(|s| s.to_string())
            .collect::<Vec<String>>();

        if mp_size_trimmed[0] != "msz" {
            return Err("Invalid map size".to_string());
        }

        let vs = mp_size_trimmed
            .iter()
            .skip(1)
            .map(|s| s.parse().unwrap())
            .collect::<Vec<u32>>();

        if vs.len() != 2 {
            return Err("Invalid map size".to_string());
        }

        self.map_size = (vs[0], vs[1]);

        if self.map_size != (server_options.x, server_options.y) {
            return Err("Invalid map size".to_string());
        }

        let tms = sock.get_line().map_err(|e| e.to_string())?;

        dbg!(&tms);

        let tms_trimmed = tms
            .trim_end()
            .split(' ')
            .map(|s| s.to_string())
            .collect::<Vec<String>>();

        if tms_trimmed[0] != "sgt" {
            return Err("Bad time response".to_string());
        }

        let time = tms_trimmed[1].parse::<u32>().unwrap();

        if time != server_options.frequency {
            return Err("Bad time response".to_string());
        }

        Ok(())
    }
}
