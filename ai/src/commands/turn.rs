//
// EPITECH PROJECT, 2024
// turn
// File description:
// turn 90° right and 90° left commands
//

#![allow(dead_code)]

use crate::tcp::TcpClient;

pub enum Direction {
    Left,
    Right,
}

const DIRECTIONS: [&str; 2] = ["Left", "Right"];

pub async fn turn(client: &mut TcpClient, dir: Direction) -> bool {
    if client
        .send_request(String::from(DIRECTIONS[dir as usize]) + "\n")
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
