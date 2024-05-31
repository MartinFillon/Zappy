//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// main
//

use std::env::var;
use std::process;

use log::info;
use env_logger::{Builder, Env};

pub mod ai;
pub mod commands;
pub mod flags;
pub mod json;
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
            let address: String =
                format!("{}:{}", res.clone().get_machine(), res.clone().get_port());
            match ai::launch(address, res.get_name()).await {
                Ok(_) => process::exit(SUCCESS_CODE),
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
}
