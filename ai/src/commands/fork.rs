//
// EPITECH PROJECT, 2024
// fork
// File description:
// fork command
//

#![allow(dead_code)]

use crate::tcp::command_handle::CommandHandler;
use crate::tcp::TcpClient;

// pub async fn fork(client: &mut TcpClient) -> bool {
//     if client.send_request(String::from("Fork\n")).await.is_err() {
//         return false;
//     }
//     match client.get_response().await {
//         Some(res) => {
//             print!("{res}");
//             if res == "dead\n" {
//                 return false;
//             }
//         }
//         None => return false,
//     }
//     true
// }

pub async fn fork(client: &mut TcpClient) -> bool {
    match client.check_dead("Fork\n").await {
        Ok(_) => true,
        Err(_) => false,
    }
}
