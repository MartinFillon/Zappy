use std::{fs::File, io::BufReader, path::Path, thread, time::Duration};

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
    let tester = Tester::new(opts.path);

    let mut svr = Server::new(opts.config.clone(), opts.server.clone())?;
    for test in tester.tests {
        let mut connection = Connection::new(opts.port, &opts.host).map_err(|e| e.to_string())?;

        connection
            .send(test.get_mode().to_owned())
            .map_err(|e| e.to_string())?;

        if connection.run_test(&test).map_err(|e| e.to_string())? {
            println!("Test passed");
        } else {
            println!("Test failed {:?}", test);
        }
    }
    svr.kill()?;
    Ok(())
}
