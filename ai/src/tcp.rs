//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// tcp
//

#![allow(dead_code)]

pub mod command_handle;

use crate::crypt::Crypt;

use std::io::{Error, ErrorKind};

use command_handle::DirectionMessage;
use tokio::io::{self, AsyncReadExt, AsyncWriteExt, BufReader};
use tokio::net::tcp::{OwnedReadHalf, OwnedWriteHalf};
use tokio::net::TcpStream;
use tokio::select;
use tokio::sync::mpsc::{self, Receiver, Sender};
use tokio::task::JoinHandle;

use zappy_macros::Bean;

use log::{debug, error, info, warn};

#[derive(Debug, Bean)]
pub struct TcpClient {
    addr: String,
    request_sender: Option<Sender<String>>,
    response_receiver: Option<Receiver<String>>,
    connection_handle: Option<JoinHandle<()>>,
    messages: Vec<(DirectionMessage, String)>,
    crypt: Crypt,
}

impl TcpClient {
    pub fn new(addr: &str, team: String) -> Self {
        Self {
            addr: addr.to_string(),
            request_sender: None,
            response_receiver: None,
            connection_handle: None,
            messages: Vec::new(),
            crypt: Crypt::new(team),
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
        debug!("Sending request: {}", request.trim_end());
        if let Some(sender) = &self.request_sender {
            sender
                .send(request)
                .await
                .map_err(|e| io::Error::new(io::ErrorKind::Other, e))
        } else {
            error!("Failed to send request: Not connected to server.");
            Err(io::Error::new(
                io::ErrorKind::NotConnected,
                "Not connected to server.",
            ))
        }
    }

    pub async fn get_response(&mut self) -> Option<String> {
        if let Some(receiver) = &mut self.response_receiver {
            receiver.recv().await
        } else {
            debug!("No response received, response receiver not available.");
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
                            warn!("Connection closed by the server.");
                            break;
                        }
                        Ok(n) => {
                            debug!("Read {} bytes from the server.", n);
                            let response = String::from_utf8_lossy(&buffer[..n]).to_string();
                            if let Err(e) = response_sender.send(response).await {
                                error!("Failed to send response: {}", e);
                                break;
                            }
                        }
                        Err(e) => {
                            error!("Failed to read from socket: {}", e);
                            break;
                        }
                    }
                }
                request = request_receiver.recv() => {
                    match request {
                        Some(req) => {
                            if let Err(e) = write_half.write_all(req.as_bytes()).await {
                                error!("Failed to write to socket: {}", e);
                                break;
                            }
                            debug!("Successfully wrote request to socket: `{}\\n`", req.trim_end());
                        }
                        None => {
                            warn!("Request channel closed.");
                            break;
                        }
                    }
                }
            }
        }
    }

    pub fn push_message(&mut self, message: (DirectionMessage, String)) {
        self.messages.push(message)
    }

    pub fn pop_message(&mut self) -> Option<(DirectionMessage, String)> {
        if self.messages.is_empty() {
            None
        } else {
            Some(self.messages.remove(0))
        }
    }
}

pub async fn handle_tcp(address: String, team: String) -> io::Result<TcpClient> {
    let mut client = TcpClient::new(address.as_str(), team);
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

// run the server on port 4242
#[cfg(test)]
mod tests {
    use super::handle_tcp;
    use tokio::runtime::Runtime;

    #[test]
    fn test_tcp_client() {
        let mut rt = Runtime::new().unwrap();

        rt.block_on(async {
            let address = "127.0.0.1:4242".to_string();
            let team = "Team1".to_string();

            let mut client = handle_tcp(address.clone(), team.clone()).await.unwrap();

            let request = "Team1\n".to_string();
            client.send_request(request.clone()).await.unwrap();

            let response = client.get_response().await.unwrap();
            assert!(response.ends_with("\n"));
        });
    }
}
