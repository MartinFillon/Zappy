/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_foward
*/

#include <stdbool.h>
#include "client.h"
#include "router/route.h"
#include "types/ai.h"
#include "types/map.h"

#include "types/position.h"
#include "utils.h"

static void move_pos_y(pos_t *pos, enum direction dir, map_t *map)
{
    if (dir == UP)
        pos->y = modulo(pos->y - 1, map->y);
    if (dir == DOWN)
        pos->y = (pos->y + 1) % map->y;
}

static void move_pos_x(pos_t *pos, enum direction dir, map_t *map)
{
    if (dir == LEFT)
        pos->x = modulo(pos->x - 1, map->x);
    if (dir == RIGHT)
        pos->x = (pos->x + 1) % map->x;
}

void move_by_dir(pos_t *pos, enum direction dir, map_t *map)
{
    if (dir == UP || dir == DOWN) {
        move_pos_y(pos, dir, map);
    } else {
        move_pos_x(pos, dir, map);
    }
}

void move_ai(ai_t *ai, enum direction dir, map_t *map)
{
    vec_erase_vector_int(
        map->arena[ai->pos.y][ai->pos.x].players, ai->id, &cmp_int
    );
    move_by_dir(&ai->pos, dir, map);
    vec_pushback_vector_int(map->arena[ai->pos.y][ai->pos.x].players, ai->id);
}

void handle_forward(client_t *cli, command_state_t *s)
{
    ai_t *ai = cli->ai;

    move_ai(ai, ai->dir, s->game->map);
    prepare_response_cat(&cli->io, "ok\n");
    broadcast_to(
        GUI,
        s->clients,
        "ppo %d %d %d %d\n",
        cli->ai->id,
        cli->ai->pos.x,
        cli->ai->pos.y,
        cli->ai->dir + 1
    );
}
