/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** take_on_tile
*/

#include <stdlib.h>

#include "types/map.h"
#include "types/object.h"

static void drop_food(map_t *map, size_t x, size_t y)
{
    map->arena[y][x].content.food += 1;
}

static void drop_linemate(map_t *map, size_t x, size_t y)
{
    map->arena[y][x].content.linemate += 1;
}

static void drop_deraumere(map_t *map, size_t x, size_t y)
{
    map->arena[y][x].content.deraumere += 1;
}

static void drop_sibur(map_t *map, size_t x, size_t y)
{
    map->arena[y][x].content.sibur += 1;
}

static void drop_mendiane(map_t *map, size_t x, size_t y)
{
    map->arena[y][x].content.mendiane += 1;
}

static void drop_phiras(map_t *map, size_t x, size_t y)
{
    map->arena[y][x].content.phiras += 1;
}

static void drop_thystame(map_t *map, size_t x, size_t y)
{
    map->arena[y][x].content.thystame += 1;
}

void drop_item(map_t *map, size_t x, size_t y, enum object_e obj)
{
    if (x >= map->x || y >= map->y)
        return;
    switch (obj) {
        case FOOD:
            return drop_food(map, x, y);
        case LINEMATE:
            return drop_linemate(map, x, y);
        case DERAUMERE:
            return drop_deraumere(map, x, y);
        case SIBUR:
            return drop_sibur(map, x, y);
        case MENDIANE:
            return drop_mendiane(map, x, y);
        case PHIRAS:
            return drop_phiras(map, x, y);
        case THYSTAME:
            return drop_thystame(map, x, y);
    }
}
