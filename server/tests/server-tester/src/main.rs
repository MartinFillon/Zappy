use std::path::Path;

use clap::Parser;
use parser::Opts;
use serde::Deserialize;
use test::Test;

mod connection;
mod parser;
mod test;

#[derive(Deserialize)]
struct Tester {
    tests: Vec<Test>,
}

impl Tester {
    fn new<P: AsRef<Path>>(path: P) -> Self {
        let file = std::fs::File::open(path).unwrap();
        let reader = std::io::BufReader::new(file);
        serde_json::from_reader(reader).unwrap()
    }
}

fn main() {
    let opts = Opts::parse();
    let tester = Tester::new(opts.path);
    let mut connection = connection::Connection::new(opts.port, opts.host).unwrap();

    if tester
        .tests
        .iter()
        .all(|test| connection.run_test(test).unwrap())
    {
        println!("All tests passed");
    } else {
        println!("Some tests failed");
    }
}
