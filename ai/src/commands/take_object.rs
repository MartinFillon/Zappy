//
// EPITECH PROJECT, 2024
// take_object
// File description:
// take object command
//

#![allow(dead_code)]

use crate::tcp::TcpClient;

pub async fn take_object(client: &mut TcpClient, obj: &str) -> Result<bool, bool> {
    if client
        .send_request(String::from("Take ") + obj + "\n")
        .await
        .is_err()
    {
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
        None => Err(true),
    }
}
