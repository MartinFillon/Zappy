#![allow(dead_code)]

use serde::Deserialize;
use std::fmt::Display;

use crate::client::Mode;

#[derive(Debug, Deserialize)]
pub struct Command {
    command: String,
    expected: Vec<String>,
}

#[derive(Debug, Deserialize)]
pub struct Test {
    name: String,
    description: String,
    commands: Vec<Command>,
    mode: Mode,
}

impl Display for Command {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{} -> {{", self.command)?;
        self.expected
            .iter()
            .try_for_each(|e| writeln!(f, "\t{e}"))?;
        write!(f, "}}")
    }
}

impl Test {
    pub fn get_commands(&self) -> &Vec<Command> {
        &self.commands
    }

    pub fn get_name(&self) -> &str {
        &self.name
    }
}

impl Command {
    pub fn get_command(&self) -> &str {
        &self.command
    }

    pub fn get_expected(&self) -> &Vec<String> {
        &self.expected
    }
}
