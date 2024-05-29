//
// EPITECH PROJECT, 2024
// inventory
// File description:
// inventory command
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
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
    let response = client.check_dead("Inventory\n").await?;
    read_output(response);

    Ok(())
}
