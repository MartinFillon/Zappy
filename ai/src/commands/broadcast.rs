//
// EPITECH PROJECT, 2024
// broadcast
// File description:
// broadcast command
//

#![allow(dead_code)]

use crate::tcp::TcpClient;

pub async fn broadcast(client: &mut TcpClient, msg: &str) -> bool {
    if client
        .send_request(String::from("Broadcast ") + msg + "\n")
        .await
        .is_err()
    {
        return false;
    }
    match client.get_response().await {
        Some(res) => {
            print!("{res}");
            if res == "dead\n" {
                return false;
            }
        }
        None => return false,
    }
    true
}
