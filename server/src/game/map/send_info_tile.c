/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** display_info_map
*/

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "logger.h"
#include "types/buffer.h"
#include "types/map.h"
#include "client.h"

static void check_ressource(
    io_t *io,
    char const *name,
    size_t nb_ressource,
    bool *is_first
)
{
    if (nb_ressource) {
        prepare_response_cat(io, "%s%s", (*is_first) ? "" : " ", name);
        *is_first = false;
    }
}

static void log_map_error(int y, int x, int y_max, int x_max)
{
    logs(
        ERROR_LEVEL,
        "Be careful coordinates (%d, %d) "
        "is out of range of map of size (%d, %d)\n",
        y,
        x,
        y_max,
        x_max
    );
}

void prepare_info_tile(io_t *io, map_t *map, size_t y, size_t x)
{
    bool fst = true;

    if (y > map->y || x > map->x)
        return log_map_error(y, x, map->y, map->x);
    check_ressource(io, "player", map->arena[y][x].players->size != 0, &fst);
    check_ressource(io, "food", map->arena[y][x].content.food, &fst);
    check_ressource(io, "linemate", map->arena[y][x].content.linemate, &fst);
    check_ressource(io, "deraumere", map->arena[y][x].content.deraumere, &fst);
    check_ressource(io, "sibur", map->arena[y][x].content.sibur, &fst);
    check_ressource(io, "mendiane", map->arena[y][x].content.mendiane, &fst);
    check_ressource(io, "phiras", map->arena[y][x].content.phiras, &fst);
    check_ressource(io, "thystame", map->arena[y][x].content.thystame, &fst);
}
