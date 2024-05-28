//
// EPITECH PROJECT, 2024
// inventory
// File description:
// inventory command
//

#![allow(dead_code)]

use crate::tcp::TcpClient;

fn read_output(raw: String) {
    let tmp = raw.trim_matches(|c| c == '[' || c == ']' || c == '\n');
    print!("Inventory: [ ");
    for tile in tmp.split(',') {
        if let Some(idex) = tile.rfind(' ') {
            let (item, quantity) = tile.split_at(idex);
            print!("{} = {}, ", item.trim(), quantity.trim());
        }
    }
    println!("]");
}

pub async fn inventory(client: &mut TcpClient) -> Result<(), bool> {
    if let Err(_) = client.send_request(String::from("Inventory\n")).await {
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
