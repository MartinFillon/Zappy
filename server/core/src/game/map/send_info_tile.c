/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** display_info_map
*/

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "core/client.h"
#include "core/types/buffer.h"
#include "core/types/map.h"
#include "core/types/object.h"
#include "logger.h"

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

static void prepare_info_resources(
    io_t *io,
    size_t nb_ressource,
    bool *fst,
    char const *name
)
{
    for (size_t i = 0; i < nb_ressource; i++) {
        prepare_response_cat(io, "%s%s", (*fst) ? "" : " ", name);
        *fst = false;
    }
}

void prepare_info_tile(io_t *io, map_t *map, size_t y, size_t x)
{
    bool fst = true;

    if (y > map->y || x > map->x)
        return log_map_error(y, x, map->y, map->x);
    prepare_info_resources(io, map->arena[y][x].players->size, &fst, "player");
    prepare_info_resources(io, map->arena[y][x].content[FOOD], &fst, "food");
    prepare_info_resources(
        io, map->arena[y][x].content[LINEMATE], &fst, "linemate");
    prepare_info_resources(
        io, map->arena[y][x].content[DERAUMERE], &fst, "deraumere");
    prepare_info_resources(io, map->arena[y][x].content[SIBUR], &fst, "sibur");
    prepare_info_resources(
        io, map->arena[y][x].content[MENDIANE], &fst, "mendiane");
    prepare_info_resources(
        io, map->arena[y][x].content[PHIRAS], &fst, "phiras");
    prepare_info_resources(
        io, map->arena[y][x].content[THYSTAME], &fst, "thystame");
}
