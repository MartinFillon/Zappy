//
// EPITECH PROJECT, 2024
// inventory
// File description:
// inventory command
//

#![allow(dead_code)]

use std::sync::Arc;
use crate::tcp::TcpClient;

fn read_output(raw: String) {
    print!("Inventory: [");
    for tile in raw.split(',') {
        let vals = tile.split_once(' ').unzip();
        match vals {
            (Some(item), Some(quantity)) => print!("{item} -> {quantity}, "),
            _ => {},
        }
    }
    println!("]");
}

pub async fn inventory(client: Arc<TcpClient>) -> std::io::Result<()> {
    client.clone().write_stream(String::from("Inventory\n")).await?;

    match client.clone().read_stream().await {
        Ok(res) => read_output(res),
        Err(_) => {},
    }

    Ok(())
}
