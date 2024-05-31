/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map_content
*/

#include <stdio.h>
#include <string.h>

#include "client.h"
#include "gui/defs.h"
#include "logger.h"
#include "map.h"
#include "str.h"
#include "types/map.h"
#include "router/error_callbacks.h"

static void get_and_send_tile(long x, long y, map_t *map, client_t *c)
{
    struct tile_s *tile = get_tile(map, x, y);

    if (tile == NULL)
        return INVALID_ARGS_CALLBACKS[c->type](c->fd);
    logs(DEBUG, "Retrieving tile %ld %ld\n", x, y);
    send_client(
        c,
        "bct %ld %ld %lu %lu %lu %lu %lu %lu %lu\n",
        x,
        y,
        tile->content.food,
        tile->content.linemate,
        tile->content.deraumere,
        tile->content.sibur,
        tile->content.mendiane,
        tile->content.phiras,
        tile->content.thystame
    );
}

void map_content_tile(client_t *cli, command_state_t *com)
{
    long x = 0;
    long y = 0;

    if (str_toint(&x, com->args->data[1]) || str_toint(&y, com->args->data[1]))
        return INVALID_ARGS_CALLBACKS[cli->type](cli->fd);
    get_and_send_tile(x, y, com->game->map, cli);
}

void map_content_full(client_t *cli, command_state_t *com)
{
    for (size_t y = 0; y < com->game->map->y; y++)
        for (size_t x = 0; x < com->game->map->x; x++)
            get_and_send_tile(x, y, com->game->map, cli);
}
