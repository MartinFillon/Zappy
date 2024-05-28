//
// EPITECH PROJECT, 2024
// inventory
// File description:
// inventory command
//

#![allow(dead_code)]

use crate::tcp::TcpClient;
use std::sync::Arc;

fn read_output(raw: String) {
    print!("Inventory: [");
    for tile in raw.split(',') {
        let vals = tile.split_once(' ').unzip();
        match vals {
            (Some(item), Some(quantity)) => print!("{item} -> {quantity}, "),
            _ => {}
        }
    }
    println!("]");
}

pub async fn inventory(client: Arc<TcpClient>) -> Result<(), bool> {
    match client
        .clone()
        .write_stream(String::from("Inventory\n"))
        .await
    {
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
