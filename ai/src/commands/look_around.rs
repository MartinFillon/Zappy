//
// EPITECH PROJECT, 2024
// look_around
// File description:
// look around command
//

#![allow(dead_code)]

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
    if client.send_request(String::from("Look\n")).await.is_err() {
        return Err(true);
    }
    match client.get_response().await {
        Some(res) => {
            if res == "dead\n" {
                return Err(false);
            }
            read_output(res);
        }
        None => return Err(true),
    }
    Ok(())
}