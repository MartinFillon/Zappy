//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// main
//

use std::{collections::HashMap, process};

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

#[derive(Debug, Deserialize)]
struct Test {
    a: i32,
    b: i32,
    c: i32,
}

#[tokio::main]
async fn main() {
    let mut test_object: HashMap<String, JsonValue> = HashMap::new();

    test_object.insert("a".to_string(), JsonValue::Number(1.0));
    test_object.insert("b".to_string(), JsonValue::Number(2.0));
    test_object.insert("c".to_string(), JsonValue::Number(3.0));

    let test = Test::from_value(&JsonValue::Object(test_object)).unwrap();

    println!("{:?}", test);
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
