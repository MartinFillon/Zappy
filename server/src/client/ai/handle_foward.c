/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_foward
*/

#include <stdbool.h>
#include <stdio.h>
#include "types/ai.h"
#include "types/map.h"

#include "ai/ai_cmds.h"
#include "utils.h"

static void move_y(ai_t *ai, map_t *map)
{
    int y = ai->y;

    if (ai->dir == UP)
        y = modulo(ai->y - 1, map->y);
    if (ai->dir == DOWN)
        y = (y + 1) % map->y;
    if (map->arena[y][ai->x].occupied)
        return;
    map->arena[ai->y][ai->x].occupied = false;
    map->arena[y][ai->x].occupied = true;
    ai->y = y;
}

static void move_x(ai_t *ai, map_t *map)
{
    int x = ai->x;

    if (ai->dir == LEFT)
        x = modulo(ai->x - 1, map->x);
    if (ai->dir == RIGHT)
        x = (x + 1) % map->x;
    if (map->arena[ai->y][x].occupied)
        return;
    map->arena[ai->y][ai->x].occupied = false;
    map->arena[ai->y][x].occupied = true;
    ai->x = x;
}

void handle_forward(client_t *cli, game_t *game)
{
    ai_t *ai = cli->ai;

    if (ai->dir == UP || ai->dir == DOWN) {
        move_y(ai, game->map);
    } else {
        move_x(ai, game->map);
    }
    dprintf(cli->fd, "ok\n");
}
