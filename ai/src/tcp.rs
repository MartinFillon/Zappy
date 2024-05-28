//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// tcp
//

#![allow(dead_code)]

use tokio::io::{self, AsyncBufReadExt, AsyncReadExt, AsyncWriteExt, BufReader};
use tokio::net::TcpStream;
use tokio::select;

pub struct TcpClient {
    addr: String,
}

impl TcpClient {
    pub fn new(addr: &str) -> Self {
        Self {
            addr: addr.to_string(),
        }
    }

    pub async fn run(&self) -> io::Result<()> {
        let stream = TcpStream::connect(&self.addr).await?;
        println!("Connected to the server at {}", self.addr);

        let (read_half, write_half) = stream.into_split();
        let reader = BufReader::new(read_half);

        let input_handle = tokio::spawn(Self::handle_input(write_half));

        self.read_from_server(reader, input_handle).await
    }

    async fn handle_input(mut write_half: tokio::net::tcp::OwnedWriteHalf) {
        let stdin = io::stdin();
        let mut stdin_reader = BufReader::new(stdin);

        loop {
            let mut input = String::new();
            match stdin_reader.read_line(&mut input).await {
                Ok(0) => break,
                Ok(_) => {
                    if let Err(e) = write_half.write_all(input.as_bytes()).await {
                        eprintln!("Failed to write to socket: {}", e);
                        break;
                    }
                }
                Err(e) => {
                    eprintln!("Failed to read from stdin: {}", e);
                    break;
                }
            }
        }
    }

    async fn read_from_server(
        &self,
        mut reader: BufReader<tokio::net::tcp::OwnedReadHalf>,
        mut input_handle: tokio::task::JoinHandle<()>,
    ) -> io::Result<()> {
        let mut buffer = vec![0; 1024];

        loop {
            select! {
                result = reader.read(&mut buffer) => {
                    match result {
                        Ok(0) => {
                            println!("Connection closed by the server.");
                            break;
                        }
                        Ok(n) => {
                            print!("{}", String::from_utf8_lossy(&buffer[..n]));
                        }
                        Err(e) => {
                            println!("Failed to read from socket: {}", e);
                            break;
                        }
                    }
                }
                _ = &mut input_handle => {
                    break;
                }
            }
        }

        input_handle.await.expect("Input handle task failed"); // a changer

        Ok(())
    }

    pub async fn send_request(&self, request: &'static str) -> io::Result<String> {
        let stream = TcpStream::connect(&self.addr).await?;
        let (read_half, mut write_half) = stream.into_split();

        write_half.write_all(request.as_bytes()).await?;

        let mut reader = BufReader::new(read_half);
        let mut response = String::new();
        reader.read_to_string(&mut response).await?;

        Ok(response)
    }
}
