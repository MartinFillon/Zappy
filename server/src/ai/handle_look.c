/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_look
*/


#include <stdbool.h>
#include <stdio.h>

#include "map.h"
#include "types/ai.h"
#include "types/client.h"
#include "types/map.h"
#include "utils.h"
#include "client.h"
#include "ai/ai_cmds.h"

static void update_start(pos_t *pos, enum Direction dir)
{
    pos->y += (dir == UP || dir == RIGHT) ? -1 : 1;
    pos->x += (dir == UP || dir == LEFT) ? -1 : 1;
}

static void init_add_pos(pos_t *pos, enum Direction dir)
{
    if (dir == LEFT)
        pos->y = -1;
    if (dir == RIGHT)
        pos->y = 1;
    if (dir == UP)
        pos->x = 1;
    if (dir == DOWN)
        pos->x = -1;
}

static void look_line(
    const pos_t *pos,
    size_t curr_level,
    client_t *cli,
    map_t *map
)
{
    pos_t cpy_pos = {pos->x, pos->y};
    pos_t add_pos = {0, 0};
    size_t nb_tile = (curr_level * 2) + 1;

    init_add_pos(&add_pos, cli->ai->dir);
    for (size_t k = 0; k < nb_tile; k++) {
        cpy_pos.y = modulo(cpy_pos.y, map->y);
        cpy_pos.x = modulo(cpy_pos.x, map->x);
        prepare_info_tile(&cli->io, map, cpy_pos.y, cpy_pos.x);
        if (k + 1 != nb_tile)
            prepare_response_cat(&cli->io, ",");
        cpy_pos.x += add_pos.x;
        cpy_pos.y += add_pos.y;
    }
}

void handle_look(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
)
{
    pos_t pos = {cli->ai->pos.x, cli->ai->pos.y};

    (void) clients;
    if (!is_empty(arg))
        return prepare_response(&cli->io, "ko\n");
    prepare_response_cat(&cli->io, "[");
    for (size_t i = 0; i <= cli->ai->level; i++) {
        look_line(&pos, i, cli, game->map);
        update_start(&pos, cli->ai->dir);
        if (i != cli->ai->level)
            prepare_response_cat(&cli->io, ",");
    }
    prepare_response_cat(&cli->io, "]\n");
}
