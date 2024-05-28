#![allow(dead_code)]

use std::{fs::File, io::BufReader, path::Path};

use clap::Parser;
use client::{graphic::Graphic, Client};
use connection::Connection;
use parser::Opts;
use serde::Deserialize;
use serde_json::from_reader;
use server::Server;
use test::Test;

mod client;
mod connection;
mod parser;
mod server;
mod test;
mod tile;

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

fn run_tests(opts: &Opts, svr: &mut Server, tests: Vec<Test>) -> Result<(), String> {
    for test in tests {
        let mut conn = Connection::new(opts.port, &opts.host).map_err(|e| e.to_string())?;
        let mut cli = client::new_cli(test.get_mode());
        let con_result = cli.connect(&mut conn, svr.get_options());

        if con_result.is_err() {
            println!("{}: KO", test.get_name());
            println!("Connection error: {}", con_result.unwrap_err());
            continue;
        }

        let res = cli.test(&mut conn, &test)?;
        if res.is_empty() {
            println!("{}: OK", test.get_name());
        } else {
            println!("{}: KO", test.get_name());
            println!("Results:");
            for r in res {
                println!("{}", r);
            }
        }
    }
    Ok(())
}

fn main() -> Result<(), String> {
    let opts = Opts::parse();
    let tests = Tester::new(&opts.path);

    let mut svr = Server::new(opts.config.clone(), opts.server.clone())?;

    std::thread::sleep(std::time::Duration::from_secs(1));

    run_tests(&opts, &mut svr, tests.tests)?;

    svr.kill()?;
    Ok(())
}
