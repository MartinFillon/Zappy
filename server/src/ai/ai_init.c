/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_init
*/

#include <string.h>

#include "clock.h"
#include "types/client.h"
#include "vector.h"

bool init_ai(game_t *game, client_t *client, double freq, char const *team)
{
    ai_t new = {0};

    if (game->ais->len + 1 > game->ais->size) {
        if (resize_vector_ai(game->ais))
            return true;
    }
    new.clock = clock_new(freq);
    new.team = strdup(team);
    push_back_vector_ai(game->ais, &new);
    client->ai = &new;
    return false;
}
