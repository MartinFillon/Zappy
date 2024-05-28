//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// tcp
//

#![allow(dead_code)]

use std::sync::Arc;
use tokio::io::{AsyncBufReadExt, AsyncWriteExt};
use tokio::net::TcpStream;
use tokio::sync::Mutex;
use tokio::io::AsyncReadExt;

pub struct TcpClient {
    stream: Arc<Mutex<TcpStream>>,
}

impl TcpClient {
    pub async fn new(address: &str, port: usize) -> std::io::Result<Self> {
        let addr = format!("{}:{}", address, port);
        let stream = TcpStream::connect(addr).await?;
        stream.set_nodelay(true)?;

        Ok(Self {
            stream: Arc::new(Mutex::new(stream)),
        })
    }

    pub async fn read_stream(self: Arc<Self>) -> std::io::Result<String> {
        let stream = self.stream.clone();
        tokio::spawn(async move {
            let mut res = String::new();
            let mut buf = [0; 1024];
            loop {
                let mut stream = stream.lock().await;
                match stream.read(&mut buf).await {
                    Ok(0) => break, // EOF
                    Ok(n) => {
                        if let Ok(s) = std::str::from_utf8(&buf[..n]) {
                            print!("{}", s);
                            res.push_str(s);
                            if s.ends_with('\n') {
                                break;
                            }
                        }
                    }
                    Err(e) => {
                        eprintln!("Error reading from stream: {e}");
                        break;
                    }
                }
            }
        });
        Ok(String::from("toto"))
    }

    pub async fn write_stream(&self, message: String) -> std::io::Result<()> {
        let mut stream = self.stream.lock().await;
        stream.write_all(message.as_bytes()).await?;
        stream.flush().await?;
        Ok(())
    }
}

pub async fn tcp_client(address: String, port: usize) -> std::io::Result<()> {
    let client = Arc::new(TcpClient::new(&address, port).await?);
    client.clone().read_stream().await;

    let mut stdin = tokio::io::BufReader::new(tokio::io::stdin());
    let mut line = String::new();

    while stdin.read_line(&mut line).await.unwrap_or(0) > 0 {
        print!("{line}");
        client.clone().write_stream(line.clone()).await?;
        line.clear();
    }

    Ok(())
}
