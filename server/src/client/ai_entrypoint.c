/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client_entrypoint
*/

#include <stdio.h>
#include <string.h>

#include "logger.h"
#include "types/client.h"
#include "ai/ai_cmds.h"

int ai_entrypoint(char const *line, client_t *c, game_t *game)
{
    for (int i = 0; AI_CMDS[i].name != NULL; i++) {
        if (strcmp(AI_CMDS[i].name, line) == 0) {
            AI_CMDS[i].func(c, game);
            return 0;
        }
    }
    logs(INFO, "Unknown command from client [%d]\n", c->fd);
    dprintf(c->fd, "ko\n");
    return 0;
}
