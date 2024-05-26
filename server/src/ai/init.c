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
    ai_t *new = calloc(1, sizeof(ai_t));

    if (game->ais->len + 1 > game->ais->size) {
        if (resize_vector_ai(game->ais))
            return true;
    }
    new->clock = clock_new(game->frequency);
    new->team = (team_t *)team;
    new->food_clock = clock_new(game->frequency);
    new->inventory.food = 20;
    push_back_vector_ai(game->ais, new);
    client->ai = new;
    new->alive = true;
    return false;
}
