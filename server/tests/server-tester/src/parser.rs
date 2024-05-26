use clap::{arg, Parser};

#[derive(Debug, Parser, Clone)]
#[command(about, author, version, long_about)]
#[clap(args_override_self = true)]
pub struct Opts {
    /// Path to the JSON file containing the tests
    #[arg(long)]
    pub path: String,

    /// Port to connect to
    #[arg(short, long)]
    pub port: u16,

    /// Host to connect to
    #[arg(long)]
    pub host: String,

    #[arg(long)]
    pub server: Option<String>,
}
