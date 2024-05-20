//
// EPITECH PROJECT, 2024
// Zappy
// File description:
// flags
//

use std::env::{args_os, ArgsOs};
use std::ffi::OsString;
use std::str::FromStr;

static LOCALHOST: &str = "127.0.0.1";

#[derive(Debug)]
pub struct Flags {
    port: Option<usize>,
    name: Option<String>,
    machine: String,
}

#[allow(dead_code)]
impl Flags {
    fn new() -> Flags {
        Flags {
            port: None,
            name: None,
            machine: String::from(LOCALHOST),
        }
    }

    fn set_port(&mut self, port: usize) {
        self.port = Some(port)
    }

    fn set_name(&mut self, name: String) {
        self.name = Some(name)
    }

    fn set_machine(&mut self, machine: String) {
        self.machine = machine
    }

    pub fn is_port_none(&self) -> bool {
        self.port.is_none()
    }

    pub fn is_name_none(&self) -> bool {
        self.name.is_none()
    }
}

impl std::fmt::Display for Flags {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
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
    let port: usize = parse_arg(arg_type, args.next())?;
    flags_struct.set_port(port);
    Ok(())
}

fn get_name_from_args(
    arg_type: &str,
    args: &mut ArgsOs,
    flags_struct: &mut Flags,
) -> Result<(), String> {
    let name: String = parse_arg(arg_type, args.next())?;
    flags_struct.set_name(name);
    Ok(())
}

fn get_machine_from_args(
    arg_type: &str,
    args: &mut ArgsOs,
    flags_struct: &mut Flags,
) -> Result<(), String> {
    let machine: String = parse_arg(arg_type, args.next())?;
    flags_struct.set_machine(machine);
    Ok(())
}

fn get_flags() -> Result<Flags, String> {
    let mut flags_struct = Flags::new();
    let mut args = args_os();
    args.next();

    while let Some(flag) = args.next() {
        match flag
            .into_string()
            .map_err(|_| String::from("Invalid UTF-8 Format."))?
            .as_str()
        {
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
