#![allow(dead_code)]

use std::{fs::File, io::BufReader, path::Path};

use clap::Parser;
use connection::Connection;
use parser::Opts;
use serde::Deserialize;
use serde_json::from_reader;
use server::{Server, ServerOptions};
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

fn run_tests(opts: &Opts, svr: &ServerOptions, tests: Vec<Test>) -> Result<(), String> {
    for test in tests {
        let mut conn = Connection::new(opts.port, &opts.host).map_err(|e| e.to_string())?;
        let mut cli = client::new_cli(test.get_mode());
        let con_result = cli.connect(&mut conn, svr, opts.verbose);

        if con_result.is_err() {
            println!("{}: KO", test.get_name());
            println!("Connection error: {}", con_result.unwrap_err());
            continue;
        }
        let res = cli.test(&mut conn, &test, opts.verbose)?;
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

    let svr_opts = ServerOptions::new(opts.config.clone())?;

    let svr = if !opts.no_server {
        Some(Server::new(&svr_opts, opts.server.clone())?)
    } else {
        None
    };

    std::thread::sleep(std::time::Duration::from_secs(1));

    run_tests(&opts, &svr_opts, tests.tests)?;

    svr.map(|mut s| {
        s.kill().unwrap();
        s
    });
    Ok(())
}
