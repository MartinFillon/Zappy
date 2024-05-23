use std::fmt::Display;

use serde::Deserialize;

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

impl Display for Test {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "{}: {}", self.name, self.description)?;
        writeln!(f, "Commands and their expected output:")?;
        self.commands.iter().try_for_each(|c| writeln!(f, "{c}"))
    }
}

impl Test {
    pub fn get_commands(&self) -> &Vec<Command> {
        &self.commands
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
