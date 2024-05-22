/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client_entrypoint
*/

#include <stdio.h>
#include <string.h>
#include "gui/list.h"
#include "types/client.h"

int gui_entrypoint(char const *line, client_t *c, game_t *game)
{
    char *ln_cpy = strdup(line);
    char *cmd = strtok(ln_cpy, " ");

    dprintf(2, "CMD: %s\n", cmd);
    dprintf(2, "ARGS: %s\n", ln_cpy);
    for (int i = 0; CMDS[i].cmd; i++) {
        if (strcmp(CMDS[i].cmd, cmd) == 0) {
            CMDS[i].func(ln_cpy, c, game);
            return 0;
        }
    }
    dprintf(c->fd, "suc\n");
    return 0;
}
