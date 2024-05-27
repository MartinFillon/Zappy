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

static void move_y(ai_t *ai, map_t *map)
{
    int y = ai->pos.y;

    if (ai->dir == UP)
        y = modulo(ai->pos.y - 1, map->y);
    if (ai->dir == DOWN)
        y = (y + 1) % map->y;
    ai->pos.y = y;
}

static void move_x(ai_t *ai, map_t *map)
{
    int x = ai->pos.x;

    if (ai->dir == LEFT)
        x = modulo(ai->pos.x - 1, map->x);
    if (ai->dir == RIGHT)
        x = (x + 1) % map->x;
    ai->pos.x = x;
}

void handle_forward(client_t *cli, game_t *game)
{
    ai_t *ai = cli->ai;

    if (ai->dir == UP || ai->dir == DOWN) {
        move_y(ai, game->map);
    } else {
        move_x(ai, game->map);
    }
    send_client(cli, "ok\n");
}
