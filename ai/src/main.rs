//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// main
//

use std::process;

mod flags;

static ERROR_CODE: i32 = 84;

fn main() {
    match flags::check_flags() {
        Ok(res) => println!("{}", res),
        Err(e) => {
            println!("Error: {}", e);
            flags::usage();
            process::exit(ERROR_CODE)
        }
    }
}
