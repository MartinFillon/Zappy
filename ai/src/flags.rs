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

const LOCALHOST: &str = "127.0.0.1";

const SUCCESS_CODE: i32 = 0;

#[derive(Debug, Clone)]
pub struct Flags {
    port: Option<usize>,
    name: Option<String>,
    machine: String,
}

impl Flags {
    fn set_port(&mut self, port: usize) {
        self.port = Some(port)
    }

    fn set_name(&mut self, name: String) {
        self.name = Some(name)
    }

    fn set_machine(&mut self, machine: String) {
        self.machine = machine
    }

    fn is_port_none(&self) -> bool {
        self.port.is_none()
    }

    fn is_name_none(&self) -> bool {
        self.name.is_none()
    }

    pub fn get_name(self) -> String {
        self.name.unwrap_or_default()
    }

    pub fn get_port(self) -> usize {
        self.port.unwrap_or_default()
    }

    pub fn get_machine(self) -> String {
        self.machine
    }
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
                .map_or_else(|| "None".to_string(), |p| p.to_string()),
            self.name.clone().unwrap_or_else(|| "None".to_string())
        )
    }
}

fn parse_arg<T: FromStr>(arg_type: &str, arg: Option<OsString>) -> Result<T, String> {
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
    let port: usize = dbg!(parse_arg(arg_type, args.next())?);
    flags_struct.set_port(port);
    Ok(())
}

fn get_name_from_args(
    arg_type: &str,
    args: &mut ArgsOs,
    flags_struct: &mut Flags,
) -> Result<(), String> {
    let name: String = dbg!(parse_arg(arg_type, args.next())?);
    flags_struct.set_name(name);
    Ok(())
}

fn get_machine_from_args(
    arg_type: &str,
    args: &mut ArgsOs,
    flags_struct: &mut Flags,
) -> Result<(), String> {
    let machine: String = dbg!(parse_arg(arg_type, args.next())?);
    dbg!(flags_struct.set_machine(machine));
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
    if flags.is_port_none() {
        return Err(String::from("Port is not set."));
    }
    if flags.is_name_none() {
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
