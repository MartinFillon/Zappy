/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client_entrypoint
*/

#include <stdio.h>
#include <string.h>

#include "types/client.h"
#include "ai/ai_cmds.h"
#include "utils.h"

int ai_entrypoint(
    char const *line,
    client_t *c,
    game_t *game,
    client_t *clients
)
{
    size_t size_cmd = 0;

    for (int i = 0; AI_CMDS[i].name != NULL; i++) {
        size_cmd = strlen(AI_CMDS[i].name);
        if (strncmp(AI_CMDS[i].name, line, size_cmd) == 0) {
            AI_CMDS[i].func(line + size_cmd, c, game, clients);
            return 0;
        }
    }
    logger_info("Unknown command from client [%d]\n", c->fd);
    dprintf(c->fd, "ko\n");
    return 0;
}
