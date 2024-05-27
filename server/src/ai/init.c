/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_init
*/

#include "clock.h"
#include "types/ai.h"
#include "types/client.h"
#include "types/team.h"
#include "vector.h"

bool init_ai(game_t *game, client_t *client, team_t const *team)
{
    ai_t new = {0};

    new.clock = clock_new(game->frequency);
    new.team = (team_t *)team;
    new.food_clock = clock_new(game->frequency);
    new.inventory.food = 20;
    new.alive = true;
    vec_pushback_vector_ai_t(game->ais, new);
    client->ai = &game->ais->data[game->ais->size - 1];
    return false;
}
