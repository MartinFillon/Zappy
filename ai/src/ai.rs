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

// pub async fn launch(address: String, team: String) -> io::Result<()> {
//     let mut handles = vec![];

//     let team = Arc::new(team);
//     while let Ok(client) = tcp::handle_tcp(address.clone()).await {
//         let team = Arc::clone(&team);
//         let handle = task::spawn(async move {
//             let team_str = &*team;
//             match command_handle::start_ai(client, team_str.clone()).await {
//                 Ok(_) => println!("ok"),
//                 Err(_) => println!("ko"),
//             }
//         });
//         handles.push(handle);
//     }
//     if handles.is_empty() {
//         return Err(Error::new(
//             ErrorKind::ConnectionRefused,
//             "Couldn't reach host.",
//         ));
//     }
//     for handle in handles {
//         handle.await?;
//     }
//     Ok(())
// }


// pub async fn launch(address: String, team: String) -> io::Result<()> {
//     let team = Arc::new(team);
//     // Spawn a task to continuously accept and handle new connections
//     let address_clone = address.clone();
//     let team_clone = Arc::clone(&team);

//     task::spawn(async move {
//         loop {
//             match tcp::handle_tcp(address_clone.clone()).await {
//                 Ok(client) => {
//                     let team_clone = Arc::clone(&team_clone);
//                     task::spawn(async move {
//                         let team_str = &*team_clone;
//                         match command_handle::start_ai(client, team_str.clone()).await {
//                             Ok(_) => println!("ok"),
//                             Err(_) => println!("ko"),
//                         }
//                     });
//                 },
//                 Err(err) => println!("Failed to handle TCP connection: {}", err),
//             }
//         }
//     }).await??;

//     Ok(())
// }

use tokio::net::TcpListener;
use tokio::select;

async fn handle_connection(client: tokio::net::TcpStream, team: Arc<String>) {
    let team_str = &*team;
    match command_handle::start_ai(client, team_str.clone()).await {
        Ok(_) => println!("ok"),
        Err(_) => println!("ko"),
    }
}

pub async fn launch(address: String, team: String) -> io::Result<()> {
    let team = Arc::new(team);
    let listener = TcpListener::bind(&address).await?;

    loop {
        let team_clone = Arc::clone(&team);
        select! {
            result = listener.accept() => {
                match result {
                    Ok((client, _addr)) => {
                        task::spawn(handle_connection(client, team_clone));
                    },
                    Err(err) => {
                        println!("Failed to accept connection: {}", err);
                    }
                }
            }
        }
    }

    Ok(())
}
