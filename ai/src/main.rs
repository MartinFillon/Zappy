//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// main
//

use std::process;

use env_logger::{Builder, Env};
use log::info;
use zappy_json::{DeserializeTrait, JsonValue};
use zappy_macros::Deserialize;

pub mod ai;
pub mod commands;
pub mod flags;
pub mod move_to_tile;
pub mod tcp;

const ERROR_CODE: i32 = 84;
const SUCCESS_CODE: i32 = 0;

#[derive(Deserialize)]
struct Test {
    a: i32,
    b: i32,
    c: i32,
}

#[tokio::main]
async fn main() {
    let Test = Test::from_value(JsonValue::Null).unwrap();

    // let env = Env::new().filter("ZAPPY_LOG");
    // Builder::from_env(env).init();

    // match flags::check_flags() {
    //     Ok(res) => {
    //         info!("Arguments set:\n{}", res.clone());
    //         let address: String = format!(
    //             "{}:{}",
    //             res.clone().machine(),
    //             res.clone().port().unwrap_or_default()
    //         );
    //         match ai::launch(address, res.name().clone().unwrap_or_default()).await {
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
