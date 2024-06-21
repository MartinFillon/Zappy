##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## hard_test
##

import subprocess
from config import hard_test

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
