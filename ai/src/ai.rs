//
// EPITECH PROJECT, 2024
// ai.rs
// File description:
// zappy ai main functions
//

#![allow(dead_code)]

use crate::tcp::{self, command_handle};

use std::io::{self, Error, ErrorKind};
use std::sync::Arc;

use tokio::task;

pub async fn launch(address: String, team: String) -> io::Result<()> {
    let mut handles = vec![];

    let team = Arc::new(team);
    while let Ok(client) = tcp::handle_tcp(address.clone()).await {
        let team = Arc::clone(&team);
        let handle = task::spawn(async move {
            let team_str = &*team;
            match command_handle::start_ai(client, team_str.clone()).await {
                Ok(_) => println!("ok"),
                Err(_) => println!("ko"),
            }
        });
        handles.push(handle);
    }
    if handles.is_empty() {
        return Err(Error::new(
            ErrorKind::ConnectionRefused,
            "Couldn't reach host.",
        ));
    }
    for handle in handles {
        handle.await?;
    }
    Ok(())
}
