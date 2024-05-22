use std::io::{BufReader, BufRead};
use std::net::TcpStream;

pub fn tcp(address: String, port: u32) {
    let stream = TcpStream::connect(address + ":" + &port.to_string())
        .expect("Couldn't connect to the server...");
    stream.set_nonblocking(true).expect("set_nonblocking call failed");

    let mut reader = BufReader::new(stream);
    loop {
        let mut line = String::new();
        match reader.read_line(&mut line) {
            Ok(_) => {
                print!("{line}");
                continue;
            },
            _ => {},
        };
    };
}
