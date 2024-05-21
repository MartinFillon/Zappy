/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** parse_unset
*/

#include <string.h>

#include "client.h"

int unset_entrypoint(char const *line, client_t *c, game_t *game)
{
    if (strcmp(line, "GRAPHIC") == 0) {
        c->type = GUI;
        c->entrypoint = &gui_entrypoint;
        return 0;
    }
    for (int i = 0; game->teams[i]; i++) {
        if (strcmp(line, game->teams[i]) == 0) {
            c->type = AI;
            c->entrypoint = &ai_entrypoint;
            return 0;
        }
    }
    return 1;
}
