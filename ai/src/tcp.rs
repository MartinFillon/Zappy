//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// tcp
//

#![allow(dead_code)]
use std::sync::Arc;
use tokio::io::{AsyncBufReadExt, AsyncWriteExt, BufReader};
use tokio::net::TcpStream;
use tokio::sync::Mutex;
use tokio::time::{sleep, Duration};

async fn read_stream(stream: Arc<Mutex<TcpStream>>) -> std::io::Result<()> {
    let stream_clone = stream.lock().await;
    let mut reader = BufReader::new(stream_clone);
    let timeout = Duration::from_secs(1);

    tokio::spawn(async move {
        let mut line = String::new();

        loop {
            match reader.read_line(&mut line).await {
                Ok(0) => break,
                Ok(_) => print!("{line}"),
                Err(e) => {
                    if e.kind() == std::io::ErrorKind::WouldBlock {
                        sleep(timeout).await;
                    } else {
                        eprintln!("Error reading from stream: {e}");
                        break;
                    }
                }
            }
        }
    });

    Ok(())
}

async fn write_stream(stream: Arc<Mutex<TcpStream>>, message: String) -> std::io::Result<()> {
    let mut stream = stream.lock().await;
    stream.write_all(message.as_bytes()).await?;
    stream.flush().await?;
    Ok(())
}

pub async fn tcp(address: String, port: usize) -> std::io::Result<()> {
    let addr = format!("{}:{}", address, port);
    let stream = TcpStream::connect(addr).await?;
    stream.set_nodelay(true)?;

    let stream = Arc::new(Mutex::new(stream));

    read_stream(stream.clone()).await?;

    let mut stdin = BufReader::new(tokio::io::stdin());
    let mut line = String::new();

    while stdin.read_line(&mut line).await.unwrap_or(0) > 0 {
        write_stream(stream.clone(), line.clone()).await?;
        line.clear();
    }

    Ok(())
}
