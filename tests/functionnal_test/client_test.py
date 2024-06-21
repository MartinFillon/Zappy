##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## client_test
##

import subprocess
from time import sleep
from config import ConfigTest, team_connection, cli_simple_cmds, connect_nbr_cmds
from utils import ignore_timeout, init_socket_client

def client_output_test(config: ConfigTest):
    """
        Function that launch a server and start a client with command
        specified in `config`
    """

    print(config.name)
    args = config.config.args
    server = subprocess.Popen(args=args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    sleep(1)
    cli = init_socket_client(config.cliConf.port)

    for cmd in config.cliConf.cmds:
        cli.send(cmd.encode())
        sleep(1)

    buff = cli.recv(1024)
    ignore_timeout(server, 2.0)
    server.kill()

    if buff.decode() == config.cliConf.output:
        print("\t", config.success)
    else:
        print("\t", config.failure)
    print("Output:\n", buff.decode(), sep="")
    print("VS:\n", config.cliConf.output, sep="")
    

def client_tests():
    """"
        Here we test multiple configurations:
            - `team_connection`
            - `cli_simple_cmds`
    """
    client_output_test(team_connection)
    client_output_test(cli_simple_cmds)
    client_output_test(connect_nbr_cmds)
