/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** take_on_tile
*/

#include <stdlib.h>

#include "types/map.h"
#include "types/object.h"

static bool take_food(map_t *map, size_t x, size_t y)
{
    if (map->arena[y][x].content.food > 0) {
        map->arena[y][x].content.food -= 1;
        return true;
    }
    return false;
}

static bool take_linemate(map_t *map, size_t x, size_t y)
{
    if (map->arena[y][x].content.linemate > 0) {
        map->arena[y][x].content.linemate -= 1;
        return true;
    }
    return false;
}

static bool take_deraumere(map_t *map, size_t x, size_t y)
{
    if (map->arena[y][x].content.deraumere > 0) {
        map->arena[y][x].content.deraumere -= 1;
        return true;
    }
    return false;
}

static bool take_sibur(map_t *map, size_t x, size_t y)
{
    if (map->arena[y][x].content.sibur > 0) {
        map->arena[y][x].content.sibur -= 1;
        return true;
    }
    return false;
}

static bool take_mendiane(map_t *map, size_t x, size_t y)
{
    if (map->arena[y][x].content.mendiane > 0) {
        map->arena[y][x].content.mendiane -= 1;
        return true;
    }
    return false;
}

static bool take_phiras(map_t *map, size_t x, size_t y)
{
    if (map->arena[y][x].content.phiras > 0) {
        map->arena[y][x].content.phiras -= 1;
        return true;
    }
    return false;
}

static bool take_thystame(map_t *map, size_t x, size_t y)
{
    if (map->arena[y][x].content.thystame > 0) {
        map->arena[y][x].content.thystame -= 1;
        return true;
    }
    return false;
}

bool take_item(map_t *map, size_t x, size_t y, enum object_e obj)
{
    if (x >= map->x || y >= map->y)
        return false;
    switch (obj) {
        case FOOD:
            return take_food(map, x, y);
        case LINEMATE:
            return take_linemate(map, x, y);
        case DERAUMERE:
            return take_deraumere(map, x, y);
        case SIBUR:
            return take_sibur(map, x, y);
        case MENDIANE:
            return take_mendiane(map, x, y);
        case PHIRAS:
            return take_phiras(map, x, y);
        case THYSTAME:
            return take_thystame(map, x, y);
    }
    return false;
}
