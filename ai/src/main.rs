//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// main
//

use std::process;

pub mod ai;
pub mod commands;
pub mod flags;
pub mod json;
pub mod tcp;

const ERROR_CODE: i32 = 84;
const SUCCESS_CODE: i32 = 0;

#[tokio::main]
async fn main() {
    if std::env::var("RUST_LOG").is_ok() {
        env_logger::init();
    }
    match flags::check_flags() {
        Ok(res) => {
            let address: String =
                format!("{}:{}", res.clone().get_machine(), res.clone().get_port());
            match ai::launch(address, res.get_name()).await {
                Ok(_) => process::exit(SUCCESS_CODE),
                Err(e) => {
                    eprintln!("Error: {}", e);
                    process::exit(ERROR_CODE);
                }
            }
        }
        Err(e) => {
            eprintln!("Error: {}", e);
            flags::usage();
            process::exit(ERROR_CODE)
        }
    }
}
