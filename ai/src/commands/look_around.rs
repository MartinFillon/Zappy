//
// EPITECH PROJECT, 2024
// look_around
// File description:
// look around command
//

#![allow(dead_code)]

use crate::tcp::TcpClient;
use std::sync::Arc;

fn read_output(raw: String) {
    let mut i = 0;
    for tile in raw.split(',') {
        print!("Tile {}: [", i);
        for item in tile.split(' ') {
            print!("{item} ");
        }
        println!("]");
        i += 1;
    }
}

pub async fn look_around(client: Arc<TcpClient>) -> Result<(), bool> {
    match client.clone().write_stream(String::from("Look\n")).await {
        Ok(_) => {}
        Err(_) => return Err(true),
    }
    match client.clone().read_stream().await {
        Ok(res) => {
            if res == "dead\n" {
                return Err(false);
            }
            read_output(res);
        }
        Err(_) => return Err(true),
    }
    Ok(())
}
