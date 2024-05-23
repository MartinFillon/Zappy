//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// tcp
//

#![allow(dead_code)]

use std::io::{stdin, ErrorKind::WouldBlock};
use std::io::{BufRead, BufReader, Result, Write};
use std::net::TcpStream;
use std::sync::{Arc, Mutex, MutexGuard};
use std::thread::{sleep, spawn};
use std::time::Duration;

fn read_stream(stream: Arc<Mutex<TcpStream>>) -> Result<()> {
    let stream_clone = stream.clone();
    let mut reader = BufReader::new(stream_clone.lock().unwrap().try_clone()?); // to look at and fix
    let timeout = Duration::from_secs(1);

    spawn(move || loop {
        let mut line = String::new();

        match reader.read_line(&mut line) {
            Ok(0) => break,
            Ok(_) => print!("{line}"),
            Err(ref err) if err.kind() == WouldBlock => sleep(timeout),
            Err(e) => {
                eprintln!("Error reading from stream: {e}");
                break;
            }
        }
    });

    Ok(())
}

fn write_stream(stream: Arc<Mutex<TcpStream>>, message: String) -> Result<()> {
    if let Ok(res) = stream.lock() {
        let mut stream: MutexGuard<TcpStream> = res;
        stream.write_all(message.as_bytes())?;
        stream.flush()?;
    } else {
        eprintln!("Lock error()");
        return Err(std::io::Error::from(std::io::ErrorKind::Other));
    }

    Ok(())
}

pub fn tcp(address: String, port: usize) -> Result<()> {
    let addr = format!("{}:{}", address, port);
    let stream = dbg!(TcpStream::connect(addr)?);
    stream.set_nonblocking(true)?;

    let stream = Arc::new(Mutex::new(stream));

    read_stream(stream.clone())?;

    let stdin = stdin();
    for line in stdin.lock().lines() {
        let line = line?;
        write_stream(stream.clone(), line + "\n")?;
    }

    Ok(())
}
