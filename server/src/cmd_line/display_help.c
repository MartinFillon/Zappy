/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** display_help
*/

#include <stdio.h>

void display_help(void)
{
    dprintf(
        1,
        "USAGE:\n\t./zappy_server -p port "
        "-x width -y height -n name1 name2 ... -c clientsNb -f freq -l level\n"
        "\tport\tis the port number\n"
        "\twidth\tis the width of the world\n"
        "\theight\tis the height of the world\n"
        "\tnameX\tis the name of the team X\n"
        "\tclientsNb\tis the number of authorized clients per team\n"
        "\tfreq\tis the reciprocal of time unit for execution of actions\n"
        "\tlevel\tis the level of information for logging (ERROR, INFO, "
        "WARNING, DEBUG DISABLED)\n"
    );
}
