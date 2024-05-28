#![allow(dead_code)]

use serde::Deserialize;
use serde_json::from_reader;
use std::{
    fs::File,
    io::BufReader,
    process::{Child, Command},
};

#[derive(Debug, Clone, Deserialize)]
pub struct ServerOptions {
    pub port: u32,
    pub x: u32,
    pub y: u32,
    pub teams: Vec<String>,
    pub count_per_team: u32,
    pub frequency: u32,
    pub path: Option<String>,
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
    options: ServerOptions,
}

impl ServerOptions {
    fn new(path: Option<String>) -> Result<Self, String> {
        path.map_or(Ok(ServerOptions::default()), |p| {
            let file = File::open(p);
            if file.is_ok() {
                let file = file.unwrap();
                let reader = BufReader::new(file);
                from_reader(reader).map_err(|e| e.to_string())
            } else {
                Ok(ServerOptions::default())
            }
        })
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
            .map(|process| Server {
                process,
                options: self.clone(),
            })
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

    pub fn get_options(&self) -> &ServerOptions {
        &self.options
    }
}
