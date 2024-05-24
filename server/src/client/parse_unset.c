/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** parse_unset
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client.h"
#include "macros.h"
#include "types/ai.h"
#include "types/client.h"
#include "utils.h"

static int init_ai(client_t *c, game_t *game)
{
    c->ai = calloc(1, sizeof(ai_t));
    if (!c->ai)
        return ERROR;
    c->ai->level = 1;
    c->ai->dir = rand() % 4;
    c->ai->y = rand() % game->map->y;
    c->ai->x = rand() % game->map->x;
    while (game->map->arena[c->ai->y][c->ai->x].occupied) {
        c->ai->y = rand() % game->map->y;
        c->ai->x = rand() % game->map->x;
    }
    dprintf(1, "Ai at pos (%ld, %ld)\n", c->ai->y, c->ai->x);
    game->map->arena[c->ai->y][c->ai->x].occupied = true;
    return SUCCESS;
}

int unset_entrypoint(char const *line, client_t *c, game_t *game)
{
    if (strcmp(line, "GRAPHIC") == 0) {
        logger_info("Client %d is a GUI\n", c->fd);
        c->type = GUI;
        c->entrypoint = &gui_entrypoint;
        return 0;
    }
    if (game->teams == NULL) {
        logger_warn("No teams set\n");
        return 1;
    }
    for (int i = 0; game->teams[i]; i++) {
        if (strcmp(line, game->teams[i]) == 0) {
            logger_info("Client %d is an AI\n", c->fd);
            c->type = AI;
            c->entrypoint = &ai_entrypoint;
            return init_ai(c, game);
        }
    }
    return 1;
}
