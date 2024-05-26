use std::{fs::File, io::BufReader, path::Path};

use clap::Parser;
use connection::Connection;
use parser::Opts;
use serde::Deserialize;
use serde_json::from_reader;
use server::Server;
use test::Test;

mod connection;
mod parser;
mod server;
mod test;

#[derive(Deserialize)]
struct Tester {
    tests: Vec<Test>,
}

impl Tester {
    fn new<P: AsRef<Path>>(path: P) -> Self {
        let file: File = File::open(path).unwrap();
        let reader = BufReader::new(file);
        from_reader(reader).unwrap()
    }
}

fn main() -> Result<(), String> {
    let opts = Opts::parse();
    let mut svr = Server::new(opts.server)?;
    let tester = Tester::new(opts.path);
    let mut connection = Connection::new(opts.port, opts.host).map_err(|e| e.to_string())?;

    connection
        .send("GRAPHIC".to_owned())
        .map_err(|e| e.to_string())?;
    for test in tester.tests {
        if connection.run_test(&test).map_err(|e| e.to_string())? {
            println!("Test passed");
        } else {
            println!("Test failed {test}");
        }
    }
    svr.kill()
}
