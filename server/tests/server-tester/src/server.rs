#![allow(dead_code)]

use serde::Deserialize;
use serde_json::from_reader;
use std::{
    fs::File,
    io::BufReader,
    process::{Child, Command},
};

#[derive(Debug, Clone, Deserialize)]
struct ServerOptions {
    port: u32,
    x: u32,
    y: u32,
    teams: Vec<String>,
    count_per_team: u32,
    frequency: u32,
    path: Option<String>,
}

impl Default for ServerOptions {
    fn default() -> Self {
        Self {
            port: 8080,
            x: 10,
            y: 10,
            teams: vec!["hello".to_string()],
            count_per_team: 10,
            frequency: 1,
            path: Some("./zappy_server".to_string()),
        }
    }
}

pub struct Server {
    process: Child,
}

impl ServerOptions {
    fn new(path: Option<String>) -> Result<Self, String> {
        if path.is_none() {
            return Ok(ServerOptions::default());
        }
        let file = File::open(path.unwrap());
        if file.is_ok() {
            let file = file.unwrap();
            let reader = BufReader::new(file);
            from_reader(reader).map_err(|e| e.to_string())
        } else {
            Ok(ServerOptions::default())
        }
    }

    fn run(&self, bin: Option<String>) -> Result<Server, String> {
        let mut c = Command::new(bin.unwrap_or_else(|| self.path.clone().unwrap()));

        c.arg("-p")
            .arg(format!("{}", self.port))
            .arg("-x")
            .arg(format!("{}", self.x))
            .arg("-y")
            .arg(format!("{}", self.y))
            .arg("-n");

        self.teams.iter().for_each(|team| {
            c.arg(team);
        });

        c.arg("-c")
            .arg(format!("{}", self.count_per_team))
            .arg("-f")
            .arg(format!("{}", self.frequency))
            .spawn()
            .map(|process| Server { process })
            .map_err(|e| e.to_string())
    }
}

impl Server {
    pub fn new(path: Option<String>, binary: Option<String>) -> Result<Self, String> {
        ServerOptions::new(path).and_then(|options| options.run(binary))
    }

    pub fn kill(&mut self) -> Result<(), String> {
        self.process.kill().map_err(|e| e.to_string())
    }
}