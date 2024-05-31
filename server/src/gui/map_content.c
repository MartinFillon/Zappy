/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map_content
*/

#include <stdio.h>
#include <string.h>

#include "client.h"
#include "map.h"
#include "types/map.h"

static void get_and_send_tile(long x, long y, map_t *map, client_t *c)
{
    struct tile_s *tile = get_tile(map, x, y);

    if (tile == NULL) {
        prepare_response(&c->io, "sbp\n");
        return;
    }
    prepare_response(
        &c->io,
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

static bool get_tile_pos(char *arg, long *x, long *y)
{
    char *end = NULL;

    *x = strtol(arg, &end, 10);
    if (*end != ' ' || *x < 0)
        return false;
    *y = strtol(end, &end, 10);
    if (*end != '\0' || *y < 0)
        return false;
    return true;
}

void map_content_tile(
    char *args,
    client_t *c,
    game_t *game,
    client_t *clients
)
{
    char *x = strtok(args, " \t");
    char *y = strtok(NULL, " \t");
    long px = 0;
    long py = 0;

    (void) clients;
    if (c->type != GUI)
        return;
    if (strtok(NULL, " \t") != NULL || x == NULL || y == NULL) {
        prepare_response(&c->io, "sbp\n");
        return;
    }
    if (!get_tile_pos(x, &px, &py)) {
        prepare_response(&c->io, "sbp\n");
        return;
    }
    get_and_send_tile(px, py, game->map, c);
}

void map_content_full(
    char *args,
    client_t *c,
    game_t *game,
    client_t *clients
)
{
    (void) clients;
    if (c->type != GUI)
        return;
    if (args[0] != '\0') {
        prepare_response(&c->io, "sbp\n");
        return;
    }
    for (size_t y = 0; y < game->map->y; y++) {
        for (size_t x = 0; x < game->map->x; x++) {
            get_and_send_tile(x, y, game->map, c);
        }
    }
}
