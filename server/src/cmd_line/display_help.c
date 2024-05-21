/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** display_help
*/

#include <stdio.h>

void display_help(void)
{
    dprintf(1, "USAGE: ./zappy_server -p port"
        "-x width -y height -n name1 name2 ... -c clientsNb -f freq");
}
