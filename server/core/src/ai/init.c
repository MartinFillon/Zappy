/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_init
*/

#include <stdio.h>
#include <sys/socket.h>

#include "core/client.h"
#include "core/clock.h"
#include "core/types/ai.h"
#include "core/types/client.h"
#include "core/types/object.h"
#include "core/types/team.h"
#include "logger.h"
#include "queue.h"

static void send_infos(
    int fd,
    game_t *game,
    ai_t const *new,
    struct client_list *clis
)
{
    dprintf(
        fd, "%ld\n%lu %lu\n", new->team->eggs->size, game->map->x, game->map->y
    );
    broadcast_to(
        GUI,
        clis,
        "ebo %d\npnw %d %d %d %d %d %s\n",
        new->id,
        new->id,
        new->pos.x,
        new->pos.y,
        new->dir + 1,
        new->level,
        new->team->name
    );
}

static void init_ai_info(ai_t *new, egg_t *egg, map_t *map)
{
    new->inventory = calloc(OBJ_COUNT, sizeof(size_t));
    new->inventory[FOOD] = 10;
    new->alive = true;
    new->id = egg->id;
    new->pos = egg->pos;
    new->level = 1;
    new->dir = rand() % 4;
    vec_pushback_vector_int(
        map->arena[new->pos.y][new->pos.x].players, new->id
    );
}

bool init_ai(
    game_t *game,
    client_t *restrict client,
    team_t *team,
    struct client_list *restrict clients
)
{
    ai_t *new = calloc(1, sizeof(ai_t));
    egg_t *egg = NULL;

    if (team->eggs->size == 0) {
        free(new);
        logs(
            DEBUG,
            "No more eggs to place %d in team %s\n",
            client->fd,
            team->name
        );
        return true;
    }
    egg = queue_pop_queue_egg_t(team->eggs);
    new->clock = clock_new(game->frequency);
    new->team = team;
    new->food_clock = clock_new(game->frequency);
    init_ai_info(new, egg, game->map);
    free(egg);
    vec_pushback_vector_ai_t(game->ais, new);
    client->ai = new;
    send_infos(client->fd, game, new, clients);
    logs(WARNING, "Client %d AI %d is an AI\n", client->fd, client->ai->id);
    return false;
}
