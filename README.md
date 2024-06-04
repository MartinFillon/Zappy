# ZAPPY
Zappy a epitech project

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

## Debugging/ Logging (AI)

The AI has a logging system that can be enabled by setting the `RUST_LOG` environment variable to `debug`, `trace` or `info` before running the binary.

```sh
ZAPPY_LOG=info ./zappy_ai
```

## Our team
| [<img src="https://avatars.githubusercontent.com/u/109749395?v=4" width=85><br><sub>Lou Onezime</sub>](https://github.com/louonezime) | [<img src="https://avatars.githubusercontent.com/u/114775771?v=4" width=85><br><sub>Martin Fillon</sub>](https://github.com/MartinFillon) | [<img src="https://avatars.githubusercontent.com/u/100275038?v=4" width=85><br><sub>Alexandre Vigoureux</sub>](https://github.com/Aluxray) | [<img src="https://avatars.githubusercontent.com/u/114816489?v=4" width=85><br><sub>Tiphaine Bertone</sub>](https://github.com/Kanda09) | [<img src="https://avatars.githubusercontent.com/u/105550975?v=4" width=85><br><sub>Manuel Tome</sub>](https://github.com/ManuelR-T)| [<img src="https://avatars.githubusercontent.com/u/114925763?v=4" width=85><br><sub>Rahul Chander</sub>](https://github.com/RahulCHANDER25)|
| :------------: | :------------: | :------------: | :------------: | :------------: | :------------: |