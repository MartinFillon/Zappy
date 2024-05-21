/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client_entrypoint
*/

#include <stdio.h>
#include "types/client.h"

int ai_entrypoint(char const *line, client_t *c, game_t *game)
{
    (void)game;
    dprintf(c->fd, "ai received: %s\n", line);
    return 0;
}
