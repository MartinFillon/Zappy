use std::{
    io::{self, BufRead, BufReader, Write},
    net::TcpStream,
};

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

    pub fn send(&mut self, command: String) -> io::Result<()> {
        self.stream.write_all(command.as_bytes())?;
        self.stream.write_all(b"\n")
    }

    pub fn get_line(&mut self) -> io::Result<String> {
        let mut response = String::new();
        self.reader.read_line(&mut response)?;
        Ok(response)
    }
}
