#!/usr/bin/env python3
##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## tester
##

### IMPORT TESTS ###

from simple_test import test_timeout, test_simple_connection
from hard_test import hard_test_urandom, broadcast_test
from client_test import client_tests

### CALL TESTS ###

test_timeout()
test_simple_connection()
client_tests()
hard_test_urandom()
broadcast_test()
