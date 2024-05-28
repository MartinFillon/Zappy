//
// EPITECH PROJECT, 2024
// eject
// File description:
// eject command
//

#![allow(dead_code)]

use crate::tcp::TcpClient;

pub async fn eject(client: &mut TcpClient) -> Result<bool, bool> {
    if client.send_request(String::from("Eject\n")).await.is_err() {
        return Err(true);
    }
    match client.get_response().await {
        Some(res) => {
            print!("{res}");
            if res == "dead\n" {
                return Err(false);
            }
            if res == "ok\n" {
                Ok(true)
            } else {
                Ok(false)
            }
        }
        None => return Err(true),
    }
}
