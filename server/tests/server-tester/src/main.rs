use std::{fs::File, io::BufReader, path::Path};

use clap::Parser;
use client::Client;
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

fn main() -> Result<(), String> {
    let opts = Opts::parse();
    // let tester = Tester::new(opts.path);

    let mut svr = Server::new(opts.config.clone(), opts.server.clone())?;

    std::thread::sleep(std::time::Duration::from_secs(1));
    let mut conn = Connection::new(opts.port, &opts.host).map_err(|e| e.to_string())?;
    let mut graphic = client::Graphic::default();
    dbg!(&graphic);
    graphic.connect(&mut conn, svr.get_options())?;

    svr.kill()?;
    Ok(())
}
