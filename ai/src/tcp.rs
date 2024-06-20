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
use tokio::io::{self, AsyncBufReadExt, AsyncReadExt, AsyncWriteExt, BufReader};
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
    id: usize,
}

impl TcpClient {
    pub fn new(addr: &str, team: String, id: usize) -> Self {
        Self {
            addr: addr.to_string(),
            request_sender: None,
            response_receiver: None,
            connection_handle: None,
            messages: Vec::new(),
            crypt: Crypt::new(team),
            id,
        }
    }

    pub async fn connect(&mut self) -> io::Result<()> {
        let stream = TcpStream::connect(&self.addr).await?;
        info!("[{}] Connected to the server at {}", self.id, self.addr);

        let (read_half, write_half) = stream.into_split();
        let reader = BufReader::new(read_half);
        let (request_sender, request_receiver) = mpsc::channel(100);
        let (response_sender, response_receiver) = mpsc::channel(100);

        self.request_sender = Some(request_sender);
        self.response_receiver = Some(response_receiver);

        let connection_handle = tokio::spawn(Self::handle_connection_line(
            reader,
            write_half,
            request_receiver,
            response_sender,
            self.id,
        ));
        self.connection_handle = Some(connection_handle);

        Ok(())
    }

    pub async fn send_request(&self, request: String) -> io::Result<()> {
        if let Some(sender) = &self.request_sender {
            sender
                .send(request)
                .await
                .map_err(|e| io::Error::new(io::ErrorKind::Other, e))
        } else {
            error!(
                "[{}] Failed to send request: Not connected to server.",
                self.id
            );
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
            warn!(
                "[{}] No response received, response receiver not available.",
                self.id
            );
            None
        }
    }

    async fn process_resp(response: String, response_sender: &Sender<String>, id: usize) -> bool {
        if let Err(e) = response_sender.send(response).await {
            error!("[{}] Failed to send response: {}", id, e);
            return false;
        }
        true
    }

    async fn handle_connection_line(
        mut reader: BufReader<OwnedReadHalf>,
        mut write_half: OwnedWriteHalf,
        mut request_receiver: Receiver<String>,
        response_sender: Sender<String>,
        id: usize,
    ) {
        loop {
            let mut buffer = String::new();

            select! {
                result = reader.read_line(&mut buffer) => {
                    match result {
                        Ok(0) => {
                            warn!("[{}] Connection closed by the server.", id);
                            break;
                        }
                        Ok(n) => {
                            debug!("[{}] Read {} bytes from the server.", id, n);
                            let response = buffer.trim().to_string();
                            debug!("[{}] Received: '{}\\n'", id, response.trim_end());
                            if !Self::process_resp(response, &response_sender, id).await {
                                break;
                            }
                        }
                        Err(e) => {
                            error!("[{}] Failed to read from socket: {}", id, e);
                            break;
                        }
                    }
                }
                request = request_receiver.recv() => {
                    match request {
                        Some(req) => {
                            if let Err(e) = write_half.write_all(req.as_bytes()).await {
                                error!("[{}] Failed to write to socket: {}", id, e);
                                break;
                            }
                            debug!("[{}] ai-client> `{}\\n`", id, req.trim_end());
                        }
                        None => {
                            warn!("[{}] Request channel closed.", id);
                            break;
                        }
                    }
                }
            }
            buffer.clear();
        }
    }

    async fn handle_connection(
        mut reader: BufReader<OwnedReadHalf>,
        mut write_half: OwnedWriteHalf,
        mut request_receiver: Receiver<String>,
        response_sender: Sender<String>,
        id: usize,
    ) {
        let mut buffer = vec![0; 1024];

        loop {
            select! {
                result = reader.read(&mut buffer) => {
                    match result {
                        Ok(0) => {
                            warn!("[{}] Connection closed by the server.", id);
                            break;
                        }
                        Ok(n) => {
                            debug!("[{}] Read {} bytes from the server.", id, n);
                            let response = String::from_utf8_lossy(&buffer[..n]).to_string();
                            if let Err(e) = response_sender.send(response).await {
                                error!("[{}] Failed to send response: {}", id, e);
                                break;
                            }
                        }
                        Err(e) => {
                            error!("[{}] Failed to read from socket: {}", id, e);
                            break;
                        }
                    }
                }
                request = request_receiver.recv() => {
                    match request {
                        Some(req) => {
                            if let Err(e) = write_half.write_all(req.as_bytes()).await {
                                error!("[{}] Failed to write to socket: {}", id, e);
                                break;
                            }
                            debug!("[{}] Successfully wrote request to socket: `{}\\n`", id, req.trim_end());
                        }
                        None => {
                            warn!("[{}] Request channel closed.", id);
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

pub async fn handle_tcp(address: String, team: String, id: usize) -> io::Result<TcpClient> {
    let mut client = TcpClient::new(address.as_str(), team, id);
    client.connect().await?;

    if let Some(response) = client.get_response().await {
        println!("[{}] server> {}", id, response);
    } else {
        return Err(Error::new(
            ErrorKind::ConnectionRefused,
            "Couldn't reach host.",
        ));
    }
    Ok(client)
}

// run the server with default values
#[cfg(test)]
mod tests {
    use super::handle_tcp;

    use std::process::{Child, Command};
    use std::time::Duration;
    use tokio::runtime::Runtime;
    use tokio::time::sleep;

    #[cfg(feature = "server_test")]
    #[test]
    fn test_tcp_client() {
        let rt = Runtime::new().unwrap();

        rt.block_on(async {
            let address = "127.0.0.1:8080".to_string();
            let team = "Team1".to_string();

            let mut client = handle_tcp(address.clone(), team.clone(), 0).await.unwrap();

            let request = "Team1\n".to_string();
            client.send_request(request.clone()).await.unwrap();

            let response = client.get_response().await.unwrap();
            assert_ne!(response, "ko");
        });
    }

    #[cfg(feature = "server_test")]
    #[test]
    fn test_tcp_client_err() {
        let rt = Runtime::new().unwrap();

        rt.block_on(async {
            let address = "127.0.0.1:8080".to_string();
            let team: String = "Team10".to_string();

            let mut client = handle_tcp(address.clone(), team.clone(), 0).await.unwrap();

            let request = "Team10\n".to_string();
            client.send_request(request.clone()).await.unwrap();

            let response = client.get_response().await.unwrap();
            assert_eq!(response, "ko");
        });
    }

    #[cfg(feature = "server_test")]
    fn start_server() -> Child {
        let server_path = "./zappy_server";

        Command::new(server_path)
            .arg("-n")
            .arg("Team1")
            .spawn()
            .expect("Failed to start server")
    }

    #[cfg(feature = "server_test")]
    fn stop_server(child: &mut Child) {
        child.kill().expect("Failed to kill server");
    }

    #[cfg(feature = "server_test")]
    #[tokio::test]
    async fn test_tcp_client_alias() {
        let mut server = start_server();
        sleep(Duration::from_secs(2)).await;

        let address = "127.0.0.1:8080".to_string();
        let team = "Team1".to_string();

        let mut client = handle_tcp(address.clone(), team.clone(), 0).await.unwrap();

        let request = "Team1\n".to_string();
        client.send_request(request.clone()).await.unwrap();

        let response = client.get_response().await.unwrap();
        assert_ne!(response, "ko");

        stop_server(&mut server);
    }

    #[cfg(feature = "server_test")]
    #[tokio::test]
    async fn test_tcp_client_err_alias() {
        let mut server = start_server();
        sleep(Duration::from_secs(2)).await;

        let address = "127.0.0.1:8080".to_string();
        let team: String = "Team10".to_string();

        let mut client = handle_tcp(address.clone(), team.clone(), 0).await.unwrap();

        let request = "Team10\n".to_string();
        client.send_request(request.clone()).await.unwrap();

        let response = client.get_response().await.unwrap();
        assert_eq!(response, "ko");

        stop_server(&mut server);
    }
}
