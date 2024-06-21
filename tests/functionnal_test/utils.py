##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## utils
##

import subprocess
from typing import IO


def ignore_timeout(proc: subprocess.Popen, timeout: float):
    try:
        proc.wait(timeout)
        pass
    except subprocess.TimeoutExpired:
        pass

def get_lines(stdout: list[bytes]) -> list[str]:
    return [s.decode() for s in stdout]
