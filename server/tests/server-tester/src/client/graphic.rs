use std::collections::HashMap;

use crate::{
    connection::Connection,
    server::ServerOptions,
    test::Test,
    tile::{self, Tile},
};

use super::{Ai, Client, Position};

#[derive(Debug, Default)]
pub struct Graphic {
    map_size: (u32, u32),
    teams: Vec<String>,
    eggs: HashMap<u32, Position>,
    players: HashMap<u32, Ai>,
    map: Vec<Tile>,
    time: u32,
}

impl Graphic {
    fn read_map_size(&self, line: &str) -> Result<(u32, u32), String> {
        let mp_size_trimmed = line
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

        Ok((vs[0], vs[1]))
    }

    fn set_map_size(&mut self, s: (u32, u32)) {
        self.map_size = s;
    }

    fn read_time(&self, line: &str) -> Result<u32, String> {
        let tms_trimmed = line
            .trim_end()
            .split(' ')
            .map(|s| s.to_string())
            .collect::<Vec<String>>();

        if tms_trimmed.len() != 2 {
            return Err("Invalid time response".to_string());
        }

        if tms_trimmed[0] != "sgt" {
            return Err("Bad time response".to_string());
        }

        tms_trimmed[1].parse::<u32>().map_err(|e| e.to_string())
    }

    fn set_time(&mut self, t: u32) {
        self.time = t;
    }

    fn read_tile(&self, line: &str) -> Result<Tile, String> {
        let tile_trimmed = line
            .trim_end()
            .split(' ')
            .map(|s| s.to_string())
            .collect::<Vec<String>>();

        if tile_trimmed.len() != 10 || tile_trimmed[0] != "bct" {
            return Err("Invalid tile".to_string());
        }

        let x = tile_trimmed[1].parse::<u32>().map_err(|e| e.to_string())?;
        let y = tile_trimmed[2].parse::<u32>().map_err(|e| e.to_string())?;
        let resources: Vec<(String, u32)> = tile_trimmed[3..]
            .iter()
            .map(|s| s.parse::<u32>().unwrap())
            .zip(tile::RESOURCES.iter())
            .map(|(a, b)| (b.to_string(), a))
            .collect();

        let mut tile = Tile::new(x, y);

        resources.iter().for_each(|(r, a)| {
            tile.new_resource(r.to_string(), *a);
        });

        Ok(tile)
    }

    fn read_map(&self, sock: &mut Connection, verbose: bool) -> Result<Vec<Tile>, String> {
        let mut tiles = Vec::new();

        for _ in 0..self.map_size.0 * self.map_size.1 {
            let mut line = sock.get_line().map_err(|e| e.to_string())?;
            line = line.trim_end().to_string();

            if verbose {
                println!("Received: {}", line);
            }
            let tile = self.read_tile(&line)?;
            tiles.push(tile);
        }

        Ok(tiles)
    }

    fn set_map(&mut self, tiles: Vec<Tile>) {
        self.map = tiles;
    }

    fn set_teams(&mut self, teams: Vec<String>) {
        self.teams = teams;
    }

    fn read_teams(&self, line: &str) -> Result<Vec<String>, String> {
        let teams_trimmed = line
            .trim_end()
            .split(' ')
            .map(|s| s.to_string())
            .collect::<Vec<String>>();

        if teams_trimmed.len() < 2 || teams_trimmed[0] != "tna" {
            return Err("Invalid teams".to_string());
        }

        Ok(teams_trimmed
            .iter()
            .skip(1)
            .map(|s| s.to_string())
            .collect())
    }

    fn read_egg(&self, line: &str) -> Result<(u32, Position), String> {
        let egg_trimmed = line
            .trim_end()
            .split(' ')
            .map(|s| s.to_string())
            .collect::<Vec<String>>();

        if egg_trimmed.len() != 5 || egg_trimmed[0] != "smg" || egg_trimmed[1] != "eni" {
            return Err("Invalid egg".to_string());
        }

        let id = egg_trimmed[2].parse::<u32>().map_err(|e| e.to_string())?;
        let x = egg_trimmed[3].parse::<u32>().map_err(|e| e.to_string())?;
        let y = egg_trimmed[4].parse::<u32>().map_err(|e| e.to_string())?;

        Ok((id, Position { x, y }))
    }
}

impl Client for Graphic {
    fn connect(
        &mut self,
        sock: &mut Connection,
        server_options: &ServerOptions,
        verbose: bool,
    ) -> Result<(), String> {
        sock.send("GRAPHIC".to_string())
            .map_err(|e| e.to_string())?;

        if verbose {
            println!("Sent: GRAPHIC");
        }

        let mp_size = sock.get_line().map_err(|e| e.to_string())?;

        if verbose {
            print!("Received: {mp_size}");
        }

        self.set_map_size(self.read_map_size(&mp_size)?);
        if self.map_size != (server_options.x, server_options.y) {
            return Err("Invalid map size".to_string());
        }

        let tms = sock.get_line().map_err(|e| e.to_string())?;

        if verbose {
            print!("Received: {tms}");
        }
        self.set_time(self.read_time(&tms)?);
        if self.time != server_options.frequency {
            return Err("Bad time response".to_string());
        }

        self.set_map(self.read_map(sock, verbose)?);
        for _ in 0..server_options.teams.len() {
            let line = sock.get_line().map_err(|e| e.to_string())?;
            print!("Received: {line}");
            self.set_teams(self.read_teams(&line)?);
        }

        if self.teams != server_options.teams {
            return Err("Invalid teams".to_string());
        }

        for _ in 0..server_options.count_per_team {
            let line = sock.get_line().map_err(|e| e.to_string())?;
            print!("Received: {line}");
            let (id, pos) = self.read_egg(&line)?;
            self.eggs.insert(id, pos);
        }

        if self.eggs.len() != server_options.count_per_team as usize * server_options.teams.len() {
            return Err("Invalid eggs".to_string());
        }
        Ok(())
    }

    fn test(
        &mut self,
        sock: &mut Connection,
        test: &Test,
        verbose: bool,
    ) -> Result<Vec<String>, String> {
        test.get_commands().iter().try_fold(Vec::new(), |mut r, c| {
            sock.send(c.get_command().to_string())
                .map_err(|e| e.to_string())?;

            if verbose {
                println!("Sent: {}", c.get_command());
            }

            c.get_expected()
                .iter()
                .try_for_each(|e| {
                    let line = sock.get_line().map_err(|e| e.to_string())?;
                    let trimmed = line.trim_end().to_string();
                    if verbose {
                        println!("Received: {}", trimmed);
                    }
                    if trimmed != *e {
                        Err(format!("Expected: {}, got: {}", e, trimmed))
                    } else {
                        Ok(())
                    }
                })
                .map_err(|e| r.push(e))
                .unwrap_or(());

            Ok(r)
        })
    }
}
