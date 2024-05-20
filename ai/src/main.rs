//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// main
//

use std::{env, process};

fn main() {
    let mut args = env::args_os();
    args.next();

    if let Some(flag) = args.next() {
        if flag.into_string().is_ok() {
        } else {
            eprintln!("Argument")
        }
    }
}
