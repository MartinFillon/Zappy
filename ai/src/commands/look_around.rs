//
// EPITECH PROJECT, 2024
// look_around
// File description:
// look around command
//

#![allow(dead_code)]

use std::sync::Arc;
use crate::tcp::TcpClient;

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

pub async fn look_around(client: Arc<TcpClient>) -> std::io::Result<()> {
    client.clone().write_stream(String::from("Look\n")).await?;

    match client.clone().read_stream().await {
        Ok(res) => read_output(res),
        Err(_) => {},
    }

    Ok(())
}
