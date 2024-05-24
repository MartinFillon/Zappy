use std::{
    fs::File,
    io::{self, BufReader},
    path::Path,
};

use clap::Parser;
use connection::Connection;
use parser::Opts;
use serde::Deserialize;
use serde_json::from_reader;
use test::Test;

mod connection;
mod parser;
mod test;

#[derive(Deserialize)]
struct Tester {
    mode: String,
    tests: Vec<Test>,
}

impl Tester {
    fn new<P: AsRef<Path>>(path: P) -> Self {
        let file = File::open(path).unwrap();
        let reader = BufReader::new(file);
        from_reader(reader).unwrap()
    }
}

fn main() -> io::Result<()> {
    let opts = Opts::parse();
    let tester = Tester::new(opts.path);
    let mut connection = Connection::new(opts.port, opts.host).unwrap();

    connection.send(tester.mode)?;
    for test in tester.tests {
        if connection.run_test(&test)? {
            println!("Test passed");
        } else {
            println!("Test failed {test}");
        }
    }
    Ok(())
}
