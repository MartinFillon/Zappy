/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_init
*/

#include <stdlib.h>
#include "clock.h"
#include "types/ai.h"
#include "types/client.h"
#include "types/team.h"

static void init_ai_infos(ai_t *new, game_t *game)
{
    new->level = 1;
    new->dir = rand() % 4;
    new->pos.y = rand() % game->map->y;
    new->pos.x = rand() % game->map->x;
    new->id = random();
    vec_pushback_vector_int(
        game->map->arena[new->pos.y][new->pos.x].players, new->id);
}

bool init_ai(game_t *game, client_t *client, team_t const *team)
{
    ai_t new = {0};

    new.clock = clock_new(game->frequency);
    new.team = (team_t *)team;
    new.food_clock = clock_new(game->frequency);
    new.inventory.food = 20;
    new.alive = true;
    init_ai_infos(&new, game);
    vec_pushback_vector_ai_t(game->ais, new);
    client->ai = &game->ais->data[game->ais->size - 1];
    return false;
}
