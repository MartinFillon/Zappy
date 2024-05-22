//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// tcp
//

#![allow(dead_code)]

use std::io::{self, BufRead, BufReader, Result};
use std::net::TcpStream;
use std::time::Duration;

pub fn tcp(address: String, port: usize) -> Result<()> {
    let addr = dbg!(format!("{}:{}", address, port));
    let stream = TcpStream::connect(&addr)?;
    stream.set_nonblocking(true)?;

    let mut reader = BufReader::new(stream);
    let timeout = Duration::from_secs(5);

    loop {
        let mut line = String::new();
        match reader.read_line(&mut line) {
            Ok(0) => {
                break;
            }
            Ok(_) => {
                print!("{line}");
            }
            Err(ref err) if err.kind() == io::ErrorKind::WouldBlock => {
                std::thread::sleep(timeout);
            }
            Err(e) => {
                eprintln!("Error reading from stream: {}", e);
                return Err(e);
            }
        }
    }
    Ok(())
}
