//
// EPITECH PROJECT, 2024
// move_up
// File description:
// move command
//

#![allow(dead_code)]

use crate::tcp::TcpClient;
use std::sync::Arc;

pub async fn move_up(client: &mut TcpClient) -> bool {
    if client.send_request(String::from("Forward\n")).await.is_err() {
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
