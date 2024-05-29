//
// EPITECH PROJECT, 2024
// incantation
// File description:
// incantation command
//

#![allow(dead_code)]

use crate::tcp::TcpClient;

pub async fn incantation(client: &mut TcpClient) -> Result<Option<usize>, bool> {
    if client
        .send_request(String::from("Incantation\n"))
        .await
        .is_err()
    {
        return Err(true);
    }
    match client.get_response().await {
        Some(res1) => {
            print!("{res1}");
            if res1 == "dead\n" {
                return Err(false);
            }
            if res1 == "Elevation underway\n" {
                match client.get_response().await {
                    Some(res2) => {
                        print!("{res2}");
                        if res2 == "ko\n" {
                            Ok(None)
                        } else {
                            match res2.trim_end().split_once(": ") {
                                Some((_, nb)) => match nb.parse::<usize>() {
                                    Ok(k) => Ok(Some(k)),
                                    Err(_) => Err(true),
                                },
                                None => Err(true),
                            }
                        }
                    }
                    None => Err(true),
                }
            } else {
                Ok(None)
            }
        }
        None => Err(true),
    }
}
