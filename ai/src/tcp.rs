//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// tcp
//

#![allow(dead_code)]

use std::io::{Error, ErrorKind};
use tokio::io::{self, AsyncReadExt, AsyncWriteExt, BufReader};
use tokio::net::tcp::{OwnedReadHalf, OwnedWriteHalf};
use tokio::net::TcpStream;
use tokio::select;
use tokio::sync::mpsc::{self, Receiver, Sender};
use tokio::task::JoinHandle;

use log::{debug, info};

pub mod command_handle;

pub struct TcpClient {
    addr: String,
    request_sender: Option<Sender<String>>,
    response_receiver: Option<Receiver<String>>,
    connection_handle: Option<JoinHandle<()>>,
}

impl TcpClient {
    pub fn new(addr: &str) -> Self {
        Self {
            addr: addr.to_string(),
            request_sender: None,
            response_receiver: None,
            connection_handle: None,
        }
    }

    pub async fn connect(&mut self) -> io::Result<()> {
        let stream = TcpStream::connect(&self.addr).await?;
        info!("Connected to the server at {}", self.addr);

        let (read_half, write_half) = stream.into_split();
        let reader = BufReader::new(read_half);
        let (request_sender, request_receiver) = mpsc::channel(100);
        let (response_sender, response_receiver) = mpsc::channel(100);

        self.request_sender = Some(request_sender);
        self.response_receiver = Some(response_receiver);

        let connection_handle = tokio::spawn(Self::handle_connection(
            reader,
            write_half,
            request_receiver,
            response_sender,
        ));
        self.connection_handle = Some(connection_handle);

        Ok(())
    }

    pub async fn send_request(&self, request: String) -> io::Result<()> {
        info!("Sending request: {}", request);
        if let Some(sender) = &self.request_sender {
            sender
                .send(request)
                .await
                .map_err(|e| io::Error::new(io::ErrorKind::Other, e))
        } else {
            Err(io::Error::new(
                io::ErrorKind::NotConnected,
                "Not connected to server.",
            ))
        }
    }

    pub async fn get_response(&mut self) -> Option<String> {
        info!("Getting response...");
        if let Some(receiver) = &mut self.response_receiver {
            info!("Response received.");
            receiver.recv().await
        } else {
            debug!("No response received.");
            None
        }
    }

    async fn handle_connection(
        mut reader: BufReader<OwnedReadHalf>,
        mut write_half: OwnedWriteHalf,
        mut request_receiver: Receiver<String>,
        response_sender: Sender<String>,
    ) {
        let mut buffer = vec![0; 1024];

        loop {
            select! {
                result = reader.read(&mut buffer) => {
                    match result {
                        Ok(0) => {
                            info!("Connection closed by the server.");
                            break;
                        }
                        Ok(n) => {
                            let response = String::from_utf8_lossy(&buffer[..n]).to_string();
                            if let Err(e) = response_sender.send(response).await {
                                debug!("Failed to send response: {}", e);
                                break;
                            }
                        }
                        Err(e) => {
                            debug!("Failed to read from socket: {}", e);
                            break;
                        }
                    }
                }
                request = request_receiver.recv() => {
                    match request {
                        Some(req) => {
                            if let Err(e) = write_half.write_all(req.as_bytes()).await {
                                debug!("Failed to write to socket: {}", e);
                                break;
                            }
                        }
                        None => {
                            debug!("Request channel closed.");
                            break;
                        }
                    }
                }
            }
        }
    }
}

pub async fn handle_tcp(address: String) -> io::Result<TcpClient> {
    let mut client = TcpClient::new(address.as_str());
    client.connect().await?;

    if let Some(response) = client.get_response().await {
        print!("server> {}", response);
    } else {
        return Err(Error::new(
            ErrorKind::ConnectionRefused,
            "Couldn't reach host.",
        ));
    }
    Ok(client)
}
