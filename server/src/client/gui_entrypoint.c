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

int gui_entrypoint(
    char const *line,
    client_t *c,
    game_t *game,
    client_t *clients
)
{
    size_t idx = (size_t)(strchrnul(line, ' ') - line);
    char *args = strdup(line + idx + 1);
    char *cmd = strndup(line, idx);

    for (int i = 0; CMDS[i].cmd; i++) {
        if (strcmp(CMDS[i].cmd, cmd) == 0) {
            CMDS[i].func(args, c, game, clients);
            return 0;
        }
    }
    dprintf(c->fd, "suc\n");
    return 0;
}
