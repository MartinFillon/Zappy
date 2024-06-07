/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** take_on_tile
*/

#include <stdlib.h>

#include "types/map.h"
#include "types/object.h"

bool take_item(map_t *map, size_t x, size_t y, enum object_e obj)
{
    if (x >= map->x || y >= map->y)
        return false;
    if (map->arena[y][x].content[obj] > 0) {
        map->arena[y][x].content[obj] -= 1;
        return true;
    }
    return false;
}
