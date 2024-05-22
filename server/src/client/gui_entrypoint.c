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
#include "utils.h"

int gui_entrypoint(char const *line, client_t *c, game_t *game)
{
    logger_debug("GUI received: %s\n", line);
    size_t idx = (size_t)(strchrnul(line, ' ') - line);
    logger_debug("IDX: %lu\n", idx);
    char *args = strdup(line + idx + 1);
    char *cmd = strndup(line, idx);

    logger_debug("CMD: %s\n", cmd);
    logger_debug("ARGS: %s\n", args);
    for (int i = 0; CMDS[i].cmd; i++) {
        if (strcmp(CMDS[i].cmd, cmd) == 0) {
            CMDS[i].func(args, c, game);
            return 0;
        }
    }
    dprintf(c->fd, "suc\n");
    return 0;
}
