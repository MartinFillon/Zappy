#![allow(dead_code)]

use std::collections::HashMap;

use graphic::Graphic;
use serde::Deserialize;
use unset::Unset;

use crate::{connection::Connection, server::ServerOptions, test::Test};

mod graphic;
mod unset;

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
struct Ai {
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
        Mode::Graphic => Box::<Graphic>::default(),
        Mode::Ai(_) => Box::<Ai>::default(),
        Mode::Unset => Box::<Unset>::default(),
    }
}
