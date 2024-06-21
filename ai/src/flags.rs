//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// flags
//

#![allow(dead_code)]

use std::env::{args_os, ArgsOs};
use std::process;

use std::ffi::OsString;
use std::str::FromStr;

use std::fmt;
use std::fmt::{Display, Formatter};

use log::{debug, info};
use zappy_macros::Bean;

const LOCALHOST: &str = "127.0.0.1";

const SUCCESS_CODE: i32 = 0;

#[derive(Debug, Clone, Bean)]
pub struct Flags {
    port: Option<usize>,
    name: Option<String>,
    machine: String,
}

impl Default for Flags {
    fn default() -> Flags {
        Flags {
            port: None,
            name: None,
            machine: String::from(LOCALHOST),
        }
    }
}

impl Display for Flags {
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
        write!(
            f,
            "Flags {{\n  Machine: {},\n  Port: {},\n  Name: {}\n}};",
            self.machine,
            self.port
                .map_or_else(|| String::from("None"), |p| p.to_string()),
            <Option<String> as Clone>::clone(&self.name).unwrap_or_default()
        )
    }
}

fn parse_arg<T: FromStr>(arg_type: &str, arg: Option<OsString>) -> Result<T, String> {
    debug!("Parsing argument for {}...", arg_type);
    arg.ok_or_else(|| format!("Flag `{}` argument is missing.", arg_type))
        .and_then(|arg| {
            arg.into_string()
                .map_err(|_| String::from("Invalid UTF-8 Format."))
        })
        .and_then(|arg| {
            arg.parse::<T>()
                .map_err(|_| format!("Failed to parse argument for {}.", arg_type))
        })
}

fn get_port_from_args(
    arg_type: &str,
    args: &mut ArgsOs,
    flags_struct: &mut Flags,
) -> Result<(), String> {
    let port: usize = parse_arg(arg_type, args.next())?;
    info!("Setting port to: {}.", port);
    flags_struct.set_port(Some(port));
    Ok(())
}

fn get_name_from_args(
    arg_type: &str,
    args: &mut ArgsOs,
    flags_struct: &mut Flags,
) -> Result<(), String> {
    let name: String = parse_arg(arg_type, args.next())?;
    info!("Setting name to: {}.", name);
    flags_struct.set_name(Some(name));
    Ok(())
}

fn get_machine_from_args(
    arg_type: &str,
    args: &mut ArgsOs,
    flags_struct: &mut Flags,
) -> Result<(), String> {
    let machine: String = parse_arg(arg_type, args.next())?;
    info!("Setting machine to: {}.", machine);
    flags_struct.set_machine(machine);
    Ok(())
}

fn get_flags() -> Result<Flags, String> {
    let mut args = args_os();
    let mut flags_struct = Flags::default();
    args.next();

    while let Some(flag) = args.next() {
        match flag
            .into_string()
            .map_err(|_| String::from("Invalid UTF-8 Format."))?
            .as_str()
        {
            "-help" => {
                usage();
                process::exit(SUCCESS_CODE);
            }
            "-p" => get_port_from_args("port", &mut args, &mut flags_struct)?,
            "-n" => get_name_from_args("name", &mut args, &mut flags_struct)?,
            "-h" => get_machine_from_args("machine", &mut args, &mut flags_struct)?,
            any => return Err(format!("Unknown flag: {}.", any)),
        };
    }
    Ok(flags_struct)
}

pub fn check_flags() -> Result<Flags, String> {
    let flags = get_flags()?;
    if flags.port().is_none() {
        return Err(String::from("Port is not set."));
    }
    if flags.name().is_none() {
        return Err(String::from("Name is not set."));
    }
    Ok(flags)
}

pub fn usage() {
    println!(
        "USAGE: ./zappy_ai -p port -n name -h machine
    -p `port` port number
    -n `name` name of the team
    -h `machine` name of the machine; localhost by default"
    )
}

#[cfg(test)]
mod test_flags {
    use super::*;

    #[test]
    fn test_parse_arg_success() {
        let arg = Some(OsString::from("8080"));
        let result: Result<usize, String> = parse_arg("port", arg);
        assert!(result.is_ok());
        assert_eq!(result.unwrap(), 8080);
    }

    #[test]
    fn test_parse_arg_missing_argument() {
        let arg: Option<OsString> = None;
        let result: Result<usize, String> = parse_arg("port", arg);
        assert!(result.is_err());
        assert_eq!(result.err().unwrap(), "Flag `port` argument is missing.");
    }

    #[test]
    fn test_parse_arg_parse_error() {
        let arg = Some(OsString::from("abc"));
        let result: Result<usize, String> = parse_arg("port", arg);
        assert!(result.is_err());
        assert_eq!(result.err().unwrap(), "Failed to parse argument for port.");
    }

    #[test]
    fn test_display_flags() {
        let flags = Flags {
            port: Some(8080),
            name: Some("team_name".to_string()),
            machine: String::from(LOCALHOST),
        };
        let expected_output =
            "Flags {\n  Machine: 127.0.0.1,\n  Port: 8080,\n  Name: team_name\n};";
        assert_eq!(format!("{}", flags), expected_output);
    }

    #[test]
    fn test_parse_arg_usize_success() {
        let args = vec![OsString::from("8080")];
        let mut args_iter = args.into_iter();
        let result: Result<usize, String> = parse_arg("port", args_iter.next());
        assert!(result.is_ok());
        assert_eq!(result.unwrap(), 8080);
    }

    #[test]
    fn test_parse_arg_string_success() {
        let args = vec![OsString::from("team_name")];
        let mut args_iter = args.into_iter();
        let result: Result<String, String> = parse_arg("name", args_iter.next());
        assert!(result.is_ok());
        assert_eq!(result.unwrap(), "team_name");
    }

    #[test]
    fn test_parse_arg_string_missing_argument() {
        let args: Vec<OsString> = vec![];
        let mut args_iter = args.into_iter();
        let result: Result<String, String> = parse_arg("name", args_iter.next());
        assert!(result.is_err());
        assert_eq!(result.err().unwrap(), "Flag `name` argument is missing.");
    }

    #[test]
    fn test_parse_arg_usize_parse_error() {
        let args = vec![OsString::from("abc")];
        let mut args_iter = args.into_iter();
        let result: Result<usize, String> = parse_arg("port", args_iter.next());
        assert!(result.is_err());
        assert_eq!(result.err().unwrap(), "Failed to parse argument for port.");
    }
}
