//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// main
//

use std::process;

use ai::{queen::Queen, AIHandler};
use elevation::Config;
use env_logger::{Builder, Env};
use log::info;

pub mod ai;
pub mod commands;
pub mod elevation;
pub mod flags;
pub mod move_to_tile;
pub mod move_towards_broadcast;
pub mod tcp;

const ERROR_CODE: i32 = 84;
const SUCCESS_CODE: i32 = 0;

#[tokio::main]
async fn main() {
    let env = Env::new().filter("ZAPPY_LOG");
    Builder::from_env(env).init();

    match flags::check_flags() {
        Ok(res) => {
            info!("Arguments set:\n{}", res.clone());
            let address: String = format!(
                "{}:{}",
                res.clone().machine(),
                res.clone().port().unwrap_or_default()
            );
            match ai::launch(address, res.name().clone().unwrap_or_default()).await {
                Ok(ai) => {
                    println!("My ai => {ai}");
                    let mut queen = Queen::new(ai);
                    if let Err(e) = queen.update().await {
                        println!("Error: {}", e);
                        process::exit(ERROR_CODE);
                    }
                }
                Err(e) => {
                    eprintln!("Error: {}.", e);
                    process::exit(ERROR_CODE);
                }
            }
        }
        Err(e) => {
            eprintln!("Error: {}.", e);
            flags::usage();
            process::exit(ERROR_CODE)
        }
    }
    process::exit(SUCCESS_CODE);
}
