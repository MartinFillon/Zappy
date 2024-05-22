/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map_content
*/

#include <stdio.h>
#include <string.h>

#include "map.h"
#include "types/client.h"
#include "types/map.h"

static void get_and_send_tile(long x, long y, map_t *map, client_t *c)
{
    struct tile_s *tile = get_tile(map, x, y);

    if (tile == NULL) {
        dprintf(c->fd, "sbp\n");
        return;
    }
    dprintf(
        c->fd,
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

void map_content_tile(char *args, client_t *c, game_t *game)
{
    char *x = strtok(args, " \t");
    char *y = strtok(NULL, " \t");
    char *end = NULL;
    long px = 0;
    long py = 0;

    if (c->type != GUI)
        return;
    if (strtok(NULL, " \t") != NULL || x == NULL || y == NULL) {
        dprintf(c->fd, "sbp\n");
        return;
    }
    px = strtol(x, &end, 10);
    if (*end != '\0' || px < 0) {
        dprintf(c->fd, "sbp\n");
        return;
    }
    py = strtol(y, &end, 10);
    if (*end != '\0' || py < 0) {
        dprintf(c->fd, "sbp\n");
        return;
    }
    get_and_send_tile(px, py, game->map, c);
}

void map_content_full(char *args, client_t *c, game_t *game)
{
    if (c->type != GUI)
        return;
    if (args[0] != '\0') {
        dprintf(c->fd, "sbp\n");
        return;
    }
    for (size_t y = 0; y < game->map->y; y++) {
        for (size_t x = 0; x < game->map->x; x++) {
            get_and_send_tile(x, y, game->map, c);
        }
    }
}
