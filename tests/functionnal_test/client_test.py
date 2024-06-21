##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## client_test
##

import subprocess
from time import sleep
from config import ConfigTest, team_connection, cli_simple_cmds
from utils import get_lines

def client_output_test(config: ConfigTest):
    """
        Function that launch a server and start a client with command
        specified in `config`
    """

    print(config.name)
    args = config.config.args
    server = subprocess.Popen(args=args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    sleep(1)
    cli = subprocess.Popen(
        args=["nc", "localhost", "8080"],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        stdin=subprocess.PIPE
    )

    for cmd in config.cli_cmd:
        print(cmd.encode())
        cli.stdin.write(cmd.encode())
        sleep(1)

    stdout, _ = cli.communicate()
    print(stdout)
    serv = server.communicate()[0]
    print(serv.decode())
    try:
        server.wait(2.0)
        cli.wait(2.0)
    except subprocess.TimeoutExpired:
        buff: str = "\n".join(get_lines(stdout.split(b"\n")))
        if buff == config.cli_output:
            print("\t", config.success)
        else:
            print("\t", config.failure)
        print("Output:\n", buff, sep="")
    

def client_tests():
    """"
        Here we test multiple configurations:
            - `team_connection`
            - `cli_simple_cmds`
    """
    # client_output_test(team_connection)
    client_output_test(cli_simple_cmds)
