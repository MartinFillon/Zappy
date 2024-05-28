#![allow(dead_code)]

use std::collections::HashMap;

use serde::Deserialize;

use crate::{connection::Connection, server::ServerOptions, test::Test};

pub mod graphic;

#[derive(Debug, Deserialize, Default, Clone, PartialEq, Eq)]
pub enum Mode {
    Graphic,    // "Graphic"
    Ai(String), // {"Ai": "team_name"}
    #[default]
    Unset,
}

#[derive(Debug, Default)]
struct Position {
    x: u32,
    y: u32,
}

#[derive(Debug, Default)]
pub struct Ai {
    position: Position,
    level: u32,
    inventory: HashMap<String, u32>,
}

pub trait Client {
    fn connect(
        &mut self,
        sock: &mut Connection,
        server_options: &ServerOptions,
        verbose: bool,
    ) -> Result<(), String>;

    fn test(
        &mut self,
        sock: &mut Connection,
        test: &Test,
        verbose: bool,
    ) -> Result<Vec<String>, String>;
}

impl Client for Ai {
    fn connect(
        &mut self,
        _sock: &mut Connection,
        _server_options: &ServerOptions,
        _verbose: bool,
    ) -> Result<(), String> {
        todo!()
    }

    fn test(
        &mut self,
        _sock: &mut Connection,
        _test: &Test,
        _verbose: bool,
    ) -> Result<Vec<String>, String> {
        todo!()
    }
}

pub fn new_cli(mode: Mode) -> Box<dyn Client> {
    match mode {
        Mode::Graphic => Box::new(graphic::Graphic::default()),
        Mode::Ai(_) => Box::new(Ai::default()),
        Mode::Unset => panic!("Mode not set"),
    }
}
