//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// main
//

use std::process;

use env_logger::{Builder, Env};
use log::info;
use rust_macros::Bean;

pub mod ai;
pub mod commands;
pub mod flags;
pub mod json;
pub mod move_to_tile;
pub mod tcp;

const ERROR_CODE: i32 = 84;
const SUCCESS_CODE: i32 = 0;

// trait Bean {
//     fn fields(&self) -> Vec<&'static str>;
// }

#[derive(Debug, Bean, Default)]
struct Test {
    b: i32,
    a: i32,
    c: i32
}

#[tokio::main]
async fn main() {
    let mut t: Test = Test::default();

    t.set_b(2);

    println!("{:?}", t);
    println!("{:?}", t.b);
    // let env = Env::new().filter("ZAPPY_LOG");
    // Builder::from_env(env).init();

    // match flags::check_flags() {
    //     Ok(res) => {
    //         info!("Arguments set:\n{}", res.clone());
    //         let address: String =
    //             format!("{}:{}", res.clone().get_machine(), res.clone().get_port());
    //         match ai::launch(address, res.get_name()).await {
    //             Ok(_) => process::exit(SUCCESS_CODE),
    //             Err(e) => {
    //                 eprintln!("Error: {}.", e);
    //                 process::exit(ERROR_CODE);
    //             }
    //         }
    //     }
    //     Err(e) => {
    //         eprintln!("Error: {}.", e);
    //         flags::usage();
    //         process::exit(ERROR_CODE)
    //     }
    // }
}
