use std::{
    io::{self, BufRead, BufReader, Write},
    net::TcpStream,
};

use crate::test::Test;

pub struct Connection {
    reader: BufReader<TcpStream>,
    stream: TcpStream,
}

impl Connection {
    pub fn new(port: u16, host: &String) -> io::Result<Self> {
        let stream = TcpStream::connect(format!("{}:{}", host, port))?;
        let mut reader = BufReader::new(stream.try_clone()?);

        let connection_response = {
            let mut response = String::new();
            reader.read_line(&mut response)?;
            response
        };

        if connection_response != "WELCOME\n" {
            Err(io::Error::new(
                io::ErrorKind::Other,
                "Failed to establish connection",
            ))
        } else {
            Ok(Self { reader, stream })
        }
    }

    pub fn run_test(&mut self, test: &Test) -> io::Result<bool> {
        println!("Running test: {}", test.get_name());
        for command in test.get_commands() {
            self.stream.write_all(command.get_command().as_bytes())?;
            self.stream.write_all(b"\n")?;
            for expected in command.get_expected() {
                let mut response = String::new();
                self.reader.read_line(&mut response)?;
                response = response.trim_end().to_string();
                if response != *expected {
                    return Ok(false);
                }
            }
        }

        Ok(true)
    }

    pub fn send(&mut self, mode: String) -> io::Result<()> {
        self.stream.write_all(mode.as_bytes())?;
        self.stream.write_all(b"\n")
    }
}
