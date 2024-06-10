/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map_content
*/

#include <stdio.h>
#include <string.h>

#include "core/client.h"
#include "core/gui/defs.h"
#include "core/map.h"
#include "core/middlewares.h"
#include "core/types/map.h"
#include "str.h"

static void get_and_send_tile(long x, long y, map_t *map, client_t *c)
{
    struct tile_s *tile = get_tile(map, x, y);

    if (tile == NULL) {
        prepare_response_cat(&c->io, "sbp\n");
        return;
    }
    prepare_response_cat(&c->io, "bct %ld %ld", x, y);
    for (size_t i = FOOD; i < OBJ_COUNT; i++)
        prepare_response_cat(&c->io, " %lu", map->arena[y][x].content[i]);
    prepare_response_cat(&c->io, "\n");
}

void map_content_tile(client_t *cli, command_state_t *com)
{
    long x = 0;
    long y = 0;

    if (str_toint(&x, com->args->data[1]) || str_toint(&y, com->args->data[1]))
        return send_invalid_args(cli);
    get_and_send_tile(x, y, com->game->map, cli);
}

void map_content_full(client_t *cli, command_state_t *com)
{
    for (size_t y = 0; y < com->game->map->y; y++)
        for (size_t x = 0; x < com->game->map->x; x++)
            get_and_send_tile(x, y, com->game->map, cli);
}
