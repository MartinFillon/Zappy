use std::collections::HashMap;

#[derive(Debug)]
pub struct Tile {
    pub x: u32,
    pub y: u32,
    pub resources: HashMap<String, u32>,
}

impl Tile {
    pub fn new(x: u32, y: u32) -> Self {
        Self {
            x,
            y,
            resources: HashMap::new(),
        }
    }

    pub fn new_resource(&mut self, resource: String, amount: u32) {
        self.resources.insert(resource, amount);
    }
}

pub static RESOURCES: [&str; 7] = [
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
];
