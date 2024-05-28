//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// main
//

use std::process;

mod flags;
mod tcp;
mod commands;

static ERROR_CODE: i32 = 84;
static SUCCESS_CODE: i32 = 0;

#[tokio::main]
async fn main() {
    match flags::check_flags() {
        Ok(res) => {
            let address: String = format!("{}:{}", res.clone().get_machine(), res.get_port());
            if let Ok(_) = tcp::handle_tcp(address).await {
                process::exit(SUCCESS_CODE);
            }
        }
        Err(e) => {
            println!("Error: {}", e);
            flags::usage();
            process::exit(ERROR_CODE)
        }
    }
}
