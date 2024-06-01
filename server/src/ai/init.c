/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_init
*/

#include <stdio.h>
#include <sys/socket.h>
#include "client.h"
#include "clock.h"
#include "queue.h"
#include "types/ai.h"
#include "types/client.h"
#include "types/team.h"

static void send_infos(int fd, game_t *game, ai_t const *new, client_t *clis)
{
    dprintf(
        fd,
        "%s\n%d\n%lu %lu\n",
        new->team->name,
        new->id,
        game->map->x,
        game->map->y
    );
    for (__auto_type i = 0; i < SOMAXCONN; i++)
        if (clis[i].fd > 0 && clis[i].type == GUI)
            prepare_response_cat(
                &clis[i].io,
                "pnw %d %d %d %d %d %s\n",
                new->id,
                new->pos.x,
                new->pos.y,
                new->dir + 1,
                new->level,
                new->team->name
            );
}

bool init_ai(
    game_t *game,
    client_t *restrict client,
    team_t *team,
    client_t *restrict clients
)
{
    ai_t new = {0};
    egg_t *egg = NULL;

    if (team->eggs->size == 0)
        return true;
    egg = queue_pop_queue_egg_t(team->eggs);
    new.clock = clock_new(game->frequency);
    new.team = team;
    new.food_clock = clock_new(game->frequency);
    new.inventory.food = 20;
    new.alive = true;
    new.id = egg->id;
    new.pos = egg->pos;
    new.level = 1;
    new.dir = rand() % 4;
    free(egg);
    vec_pushback_vector_ai_t(game->ais, new);
    client->ai = &game->ais->data[game->ais->size - 1];
    send_infos(client->fd, game, &new, clients);
    return false;
}
