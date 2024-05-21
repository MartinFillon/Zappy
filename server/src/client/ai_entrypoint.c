/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client_entrypoint
*/

#include <stdio.h>
#include "types/client.h"

int client_entrypoint(char const *line, client_t *c, game_t *game)
{
    (void)game;
    fprintf(c->ffd, "ai received: %s\n", line);
    return 0;
}
