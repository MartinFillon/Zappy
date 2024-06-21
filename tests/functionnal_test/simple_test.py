##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## timeout_test
##

import subprocess
from time import sleep
from config import timeout_config, simple_connection
from utils import ignore_timeout, init_socket_client

def test_timeout():
    """" Here we test the timeout of the server after `timeout` seconds """

    print(timeout_config.name)
    try:
        timeout = timeout_config.config.timeout
        args = timeout_config.config.args
        subprocess.run(args=args, timeout=timeout, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        print("\t", timeout_config.failure)
    except subprocess.TimeoutExpired:
        print("\t", timeout_config.success)

def test_simple_connection():
    """" Here we test a simple connection with the server """

    print(simple_connection.name)
    args = simple_connection.config.args
    server = subprocess.Popen(args=args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    sleep(1)
    cli = init_socket_client(simple_connection.cliConf.port)
    ignore_timeout(server, 2.0)

    data = cli.recv(1024)
    if data.decode() == simple_connection.cliConf.output:
        print("\t", simple_connection.success)
    else:
        print("\t", simple_connection.failure)
