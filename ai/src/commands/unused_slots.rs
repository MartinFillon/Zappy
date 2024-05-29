//
// EPITECH PROJECT, 2024
// unused_slots
// File description:
// connect_nbr command
//

#![allow(dead_code)]

use crate::tcp::TcpClient;

pub async fn unused_slots(client: &mut TcpClient) -> Result<usize, bool> {
    if client
        .send_request(String::from("Connect_nbr\n"))
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
            match res.parse::<usize>() {
                Ok(nb) => Ok(nb),
                Err(_) => Err(true),
            }
        }
        None => Err(true),
    }
}
