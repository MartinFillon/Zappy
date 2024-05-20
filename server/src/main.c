/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** main
*/

#include <stdbool.h>
#include <string.h>

#include "args_info.h"
#include "define.h"

int main(int ac, char const **av)
{
    args_infos_t args = {0};

    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        display_help();
        return SUCCESS;
    }
    if (parse_command_line(av, &args) == false)
        return EPI_ERROR;
    return SUCCESS;
}
