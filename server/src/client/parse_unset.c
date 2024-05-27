/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** parse_unset
*/

#include <stddef.h>
#include <string.h>

#include "client.h"
#include "types/client.h"
#include "types/game.h"
#include "utils.h"

static int put_in_team(client_t *c, game_t *game, size_t i)
{
    logger_info("Client %d is an AI\n", c->fd);
    c->type = AI;
    c->entrypoint = &ai_entrypoint;
    init_ai(game, c, &game->teams->data[i]);
    logger_info("AI inited\n");
    return 0;
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
    for (size_t i = 0; i < game->teams->size; i++)
        if (strcmp(line, game->teams->data[i].name) == 0)
            return put_in_team(c, game, i);
    return 1;
}
