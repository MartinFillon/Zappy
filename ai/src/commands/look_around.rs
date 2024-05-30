//
// EPITECH PROJECT, 2024
// look_around
// File description:
// look around command
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

fn read_output(raw: String) {
    let tmp = raw.trim_matches(|c| c == '[' || c == ']' || c == '\n');
    println!("{tmp}");
    for (i, tile) in tmp.split(',').enumerate() {
        print!("Tile {}: [ ", i);
        for item in tile.split(' ') {
            print!("{item} ");
        }
        println!("]");
    }
}

pub async fn look_around(client: &mut TcpClient) -> Result<(), bool> {
    let response = client.check_dead("Look\n").await?;
    read_output(response);

    Ok(())
}