/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** take_on_tile
*/

#include <stdlib.h>

#include "core/types/map.h"
#include "core/types/object.h"

void drop_item(map_t *map, size_t x, size_t y, enum object_e obj)
{
    if (x >= map->x || y >= map->y)
        return;
    map->arena[y][x].content[obj] += 1;
}
