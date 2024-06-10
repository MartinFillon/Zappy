/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** get_tile
*/

#include <stdbool.h>
#include "core/types/map.h"

struct tile_s *get_tile(map_t *map, size_t x, size_t y)
{
    if (x >= map->x || y >= map->y)
        return NULL;
    return &map->arena[y][x];
}
