/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_cmds
*/

#include <stdio.h>
#include <string.h>
#include "server.h"
#include "serv_cmd/serv_cmds.h"

void handle_server_cmd(char const *cmd, server_t *serv)
{
    for (size_t i = 0; SERV_CMDS[i].name != NULL; i++) {
        if (strcmp(SERV_CMDS[i].name, cmd) == 0) {
            SERV_CMDS[i].func(serv);
            return;
        }
    }
}
