use std::env::{ArgsOs, args_os};

static LOCALHOST: &str = "127.0.0.1";

pub struct Flags {
    pub port: Option<usize>,
    pub name: Option<String>,
    pub machine: String,
}

impl Flags {
    fn new() -> Flags {
        Flags { port: None, name: None, machine: String::from(LOCALHOST) }
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
}

fn get_port_from_args<'a>(
    args: &'a mut ArgsOs,
    flags_struct: &'a mut Flags
) -> Result<&'a mut Flags, String> {
    args.next().map(|arg| {
        match arg.into_string() {
            Ok(arg) => arg.as_str().parse::<usize>()
                            .map(|port| {
                                flags_struct.set_port(port);
                                Ok(flags_struct)
                            })
                            .expect("Failed to parse port"),
            Err(_) => Err(String::from("ArgsOs error, not a string"))
        }
    }).expect("error")
}

pub fn get_flags() -> Result<Flags, String> {
    let mut flags_struct = Flags::new();
    let mut args = args_os();

    args.next();
    while let Some(flag) = args.next() {
        if let Ok(flag) = flag.into_string() {
            match flag.as_str() {
                "-p" => get_port_from_args(&mut args, &mut flags_struct),
                //"-n" => println!("-n"),
                //"-h" => println!("-h"),
                var_str => Err(String::from("Unknown flag of value ") + var_str),
            };
        } else {
            return Err(String::from("Error"))
        }
    }
    Ok(flags_struct)
}
