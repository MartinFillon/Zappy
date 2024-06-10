/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_help
*/

#include <stdio.h>

#include "core/server.h"
#include "core/serv_cmd/serv_cmds.h"

void handle_help(zappy_t *serv, struct vector_str_t *args)
{
    (void)serv;
    (void)args;
    dprintf(1, "Supported commands:\n");
    for (size_t i = 0; SERV_CMDS[i].desc != NULL; i++) {
        dprintf(1, "    %s %s", SERV_CMDS[i].name, SERV_CMDS[i].desc);
    }
}
