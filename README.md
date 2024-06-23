# ZAPPY
Zappy a epitech project

[![Rust Pipeline](https://github.com/MartinFillon/Zappy/actions/workflows/pipeline-rust.yml/badge.svg)](https://github.com/MartinFillon/Zappy/actions/workflows/pipeline-rust.yml)[![GUI Pipeline](https://github.com/MartinFillon/Zappy/actions/workflows/pipeline-gui.yml/badge.svg)](https://github.com/MartinFillon/Zappy/actions/workflows/pipeline-gui.yml)[![Server Pipeline](https://github.com/MartinFillon/Zappy/actions/workflows/pipeline-server.yml/badge.svg)](https://github.com/MartinFillon/Zappy/actions/workflows/pipeline-server.yml)

## Compiling the project

### Dependencies

In order to compile and run the project you need the following dependencies
- `Raylib`
- `make`
- `gcc`
- `rust`
- `cargo`
- `g++`
- `asios`

### Compiling

When all of those will be installed you can run
```sh
make
```

It will compile 3 binaries:
- `zappy_gui` A Graphic renderer for the project
- `zappy_server` A Server to make the guis and ais work together
- `zappy_ai` An ai to play the game with

If you want to compile only one of the binaries you can use the following command
```sh
make <binary>
```

## Runing the project

In order to run the project you just need to run the binaries using the appropriate argumets.
It is advised to run `zappy_server` first

## Command line arguments

### Server

```sh
./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq
```

- `port`	    is the port number
- `width`	    is the width of the world
- `height`	    is the height of the world
- `nameX`	    is the name of the team X
- `clientsNb`	is the number of authorized clients per team
- `freq`	    is the reciprocal of time unit for execution of actions

It can also be runned using docker, by either building the image yourself or using the docker compose.

If you want to configure the server using the docker compose you have access to multiple env vars:

- `ZAPPY_LOG_LEVEL`     for the log level       `-l`
- `ZAPPY_TEAM_NAMES`    for the team names      `-n`
- `ZAPPY_CLIENT_NUMBER` for the client count    `-c`
- `ZAPPY_FREQUENCY`     for the frequency       `-f`
- `ZAPPY_WIDTH`         for the width           `-x`
- `ZAPPY_HEIGHT`        for the height          `-y`

## AI

```sh
./zappy_ai -p port -n name -h machine
```

- `port`    port number
- `name`    name of the team
- `machine` name of the machine; localhost by default

### AI Broadcast Protocol

Protocol of broadcasts done by the `AI(s)` to the server:

Each following broadcasts are formatted like this as requests to the server:
```bash
Broadcast <command>\n
```

| Command  | Definition | Sent by |
| -------- | ---------- | ------- |
| `<ID> waiting` | Wait for AI `Queen` to join at same tile | `Queen` |
| `<ID> assign <role> <pID>` | assign role to a new AI (by **default** considered a `Queen`) | `Queen`\|`Knight` |
-----------------------------------

- `ID` = `AI` **ID** (based off of Connection)
- `role` = role of `AI`, aka {**Bot** | **Fetus** | **Knight**}
- `pID` = player **ID** of an `AI`(based on assignation, by **default** is `0`)

## GUI

```sh
./zappy_gui -p port -h machine
```

- `port`    port number
- `machine` name of the machine; localhost by default

## Debugging/ Logging

### AI

The AI has a logging system that can be enabled by setting the `ZAPPY_LOG` environment variable to `debug`, `trace` or `info` before running the binary. For more information about it see the [env_logger](https://crates.io/crates/env_logger) crate documentation.

```sh
ZAPPY_LOG=info ./zappy_ai
```

### Server

The server also have a logging system implemented with multiple level.
The levels are set using the `-l` argument and are the following.
- `ERROR`
- `WARNING` (default)
- `INFO`
- `DEBUG`
- `DISABLE`

### GUI

The gui as a debug mode by adding the argument `-d` and the value `true` or `false` to enable or disable the log from raylib

## Code documentation

There are two main directories for the code documentation. They can be generated using `make docs`.
The directory `doc/gui` is for everything about the gui.
The directory `doc/server` is for everything about the server.
The directory `doc/ai` is for everything about the ai.

As the ai is in rust it is the only one not using a doxygen but a `cargo doc` format.


## Our team
| [<img src="https://avatars.githubusercontent.com/u/109749395?v=4" width=85><br><sub>Lou Onezime</sub>](https://github.com/louonezime) | [<img src="https://avatars.githubusercontent.com/u/114775771?v=4" width=85><br><sub>Martin Fillon</sub>](https://github.com/MartinFillon) | [<img src="https://avatars.githubusercontent.com/u/100275038?v=4" width=85><br><sub>Alexandre Vigoureux</sub>](https://github.com/Aluxray) | [<img src="https://avatars.githubusercontent.com/u/114816489?v=4" width=85><br><sub>Tiphaine Bertone</sub>](https://github.com/Kanda09) | [<img src="https://avatars.githubusercontent.com/u/105550975?v=4" width=85><br><sub>Manuel Tome</sub>](https://github.com/ManuelR-T)| [<img src="https://avatars.githubusercontent.com/u/114925763?v=4" width=85><br><sub>Rahul Chander</sub>](https://github.com/RahulCHANDER25)|
| :------------: | :------------: | :------------: | :------------: | :------------: | :------------: |