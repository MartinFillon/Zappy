//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// main
//

use std::process;

mod flags;
mod tcp;

static ERROR_CODE: i32 = 84;
static SUCCESS_CODE: i32 = 0;

#[tokio::main]
async fn main() {
    match flags::check_flags() {
        Ok(res) => {
            let address: String = format!("{}:{}", res.clone().get_machine(), res.get_port());
            let tcp_client = tcp::TcpClient::new(address.as_str());
            if let Err(e) = tcp_client.run().await {
                eprintln!("Error: {}", e);
            }
            process::exit(SUCCESS_CODE)
        }
        Err(e) => {
            println!("Error: {}", e);
            flags::usage();
            process::exit(ERROR_CODE)
        }
    }
}
