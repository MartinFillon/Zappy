##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## hard_test
##

import subprocess
from time import sleep
from config import hard_test, broadcast_cmds
from utils import ignore_timeout, init_socket_client

def hard_test_urandom():
    """
        Hard test `cat /dev/urandom | nc localhost 8080`,
        to test server integrity with huge inputs
        NOTE: To test this command, the easiest way is to use subprocess
        (other solution is socket + subprocess)
    """
    print(hard_test.name)
    args = hard_test.config.args
    server = subprocess.Popen(args=args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    urandom = subprocess.Popen(args=hard_test.cliConf.cmd_line, stdout=subprocess.PIPE)
    cli = subprocess.Popen(
        args=["nc", "localhost", "8080"],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        stdin=urandom.stdout
    )

    try:
        server.wait(4.0)
        cli.wait(4.0)
    except subprocess.TimeoutExpired:
        print("\t", hard_test.success, server.returncode)
    except subprocess.SubprocessError:
        print("\t SUBPROCESS ERROR: ", hard_test.failure)

def broadcast_test():
    """
        Test of the broadcast by connecting 2 clients
    """
    print(broadcast_cmds.name)
    args = broadcast_cmds.config.args
    server = subprocess.Popen(args=args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    sender = init_socket_client(broadcast_cmds.cliConf.port)
    receiver = init_socket_client(broadcast_cmds.cliConf.port)

    receiver.send(b"team1\n")
    for cmd in broadcast_cmds.cliConf.cmds:
        sender.send(cmd.encode())
        sleep(1)

    data_receiver = receiver.recv(1024)
    data_sender = sender.recv(1024)
    ignore_timeout(server, 2.0)
    server.kill()
    if data_receiver.decode().find("Hello") == -1:
        print(broadcast_cmds.failure, "Broadcast not received")
        return
    if data_sender.decode() == broadcast_cmds.cliConf.output:
        print("\t", broadcast_cmds.success)
    else:
        print("\t", broadcast_cmds.failure)
    print("Output:\n", data_sender.decode(), sep="")
    print("VS:\n", broadcast_cmds.cliConf.output, sep="")
    sender.close()
    receiver.close()
