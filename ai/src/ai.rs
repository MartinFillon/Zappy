//
// EPITECH PROJECT, 2024
// ai.rs
// File description:
// zappy ai main functions
//

#![allow(dead_code)]
#![allow(unused_imports)]

use crate::tcp::{self, command_handle};

use std::io::{self, Error, ErrorKind};
use std::sync::Arc;

use tokio::task;

use log::debug;

pub async fn launch(address: String, team: String) -> io::Result<()> {
    let mut handles = vec![];

    let team = Arc::new(team);
    loop {
        match tcp::handle_tcp(address.clone()).await {
            Ok(client) => {
                let team: Arc<String> = Arc::clone(&team);
                let handle = task::spawn(async move {
                    let team_str = &*team;
                    match command_handle::start_ai(client, team_str.clone()).await {
                        Ok(_) => {
                            println!("ok");
                            Ok(())
                        }
                        Err(e) => {
                            println!("ko");
                            Err(e)
                        }
                    }
                });
                handles.push(handle);
            }
            Err(e) => {
                println!("Failed to handle TCP: {}", e);
                break;
            }
        }
    }

    if handles.is_empty() {
        debug!("Connection refused, handles is empty.");
        return Err(Error::new(
            ErrorKind::ConnectionRefused,
            "Couldn't reach host.",
        ));
    }

    Ok(())
}
