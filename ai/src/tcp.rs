//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// tcp
//

#![allow(dead_code)]

use std::io::{self, BufRead, BufReader, Result, Write};
use std::net::TcpStream;
use std::thread;
use std::time::Duration;

fn read_stream(stream: &mut TcpStream) -> Result<()> {
    let mut reader = BufReader::new(stream.try_clone()?);
    let timeout = Duration::from_secs(5);

    loop {
        let mut line = String::new();
        match reader.read_line(&mut line) {
            Ok(0) => break,
            Ok(_) => print!("{line}"),
            Err(ref err) if err.kind() == io::ErrorKind::WouldBlock => {
                thread::sleep(timeout);
            }
            Err(e) => return Err(e),
        }
    }
    Ok(())
}

fn write_stream(stream: &mut TcpStream, message: String) -> Result<()> {
    stream.write_all(message.as_bytes())?;
    stream.flush()?;
    Ok(())
}

pub fn tcp(address: String, port: usize) -> Result<()> {
    let addr = dbg!(format!("{}:{}", address, port));
    let mut stream = TcpStream::connect(addr)?;
    stream.set_nonblocking(true)?;

    read_stream(&mut stream)?;

    let request = String::from("USER Anonymous");
    write_stream(&mut stream, request)?;

    Ok(())
}
