/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_cmds
*/

#include <stdio.h>
#include <string.h>
#include "logger.h"
#include "str.h"
#include "zappy.h"
#include "serv_cmd/serv_cmds.h"

void handle_server_cmd(char const *cmd, zappy_t *z)
{
    str_t *str_cmd = str_snew(cmd);
    struct vector_str_t *args = NULL;

    if (!str_cmd)
        return logs(ERROR_LEVEL, "Allocation Error\n");
    args = str_split(str_cmd, " \t");
    if (!args)
        return logs(ERROR_LEVEL, "Allocation Error\n");
    for (size_t i = 0; SERV_CMDS[i].name != NULL; i++) {
        if (strcmp(SERV_CMDS[i].name, cmd) == 0) {
            SERV_CMDS[i].func(z, args);
            return;
        }
    }
}
