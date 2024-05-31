/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_foward
*/

#include <stdbool.h>
#include "client.h"
#include "types/ai.h"
#include "types/map.h"

#include "utils.h"
#include "ai/ai_cmds.h"

void move_ai_y(ai_t *ai, enum direction dir, map_t *map)
{
    int y = ai->pos.y;

    if (dir == UP)
        y = modulo(ai->pos.y - 1, map->y);
    if (dir == DOWN)
        y = (y + 1) % map->y;
    vec_erase_vector_int(
        map->arena[ai->pos.y][ai->pos.x].players, ai->id, &cmp_int);
    ai->pos.y = y;
    vec_pushback_vector_int(
        map->arena[ai->pos.y][ai->pos.x].players, ai->id);
}

void move_ai_x(ai_t *ai, enum direction dir, map_t *map)
{
    int x = ai->pos.x;

    if (dir == LEFT)
        x = modulo(ai->pos.x - 1, map->x);
    if (dir == RIGHT)
        x = (x + 1) % map->x;
    vec_erase_vector_int(
        map->arena[ai->pos.y][ai->pos.x].players, ai->id, &cmp_int);
    ai->pos.x = x;
    vec_pushback_vector_int(map->arena[ai->pos.y][ai->pos.x].players, ai->id);
}

void handle_forward(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
)
{
    ai_t *ai = cli->ai;

    (void) clients;
    if (!is_empty(arg))
        return prepare_response(&cli->io, "ko\n");
    if (ai->dir == UP || ai->dir == DOWN) {
        move_ai_y(ai, ai->dir, game->map);
    } else {
        move_ai_x(ai, ai->dir, game->map);
    }
    prepare_response(&cli->io, "ok\n");
}
