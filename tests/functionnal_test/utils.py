##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## utils
##

import subprocess
import socket

def ignore_timeout(proc: subprocess.Popen, timeout: float):
    try:
        proc.wait(timeout)
    except subprocess.TimeoutExpired:
        print("Timeout")
        pass

def get_lines(stdout: list[bytes]) -> list[str]:
    return [s.decode() for s in stdout]

def init_socket_client(port: int) -> socket:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.connect((socket.gethostname(), port))
    except ConnectionRefusedError as err:
        print(err.strerror)
        exit(84)
    return sock
