/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** initializer
*/

#include <stdlib.h>

#include "define.h"
#include "map.h"
#include "types/map.h"

map_t *create_map(size_t x, size_t y)
{
    map_t *map = calloc(1, sizeof(map_t));

    if (map == NULL)
        return NULL;
    map->x = x;
    map->y = y;
    map->arena = calloc(y + 1, sizeof(struct tile_s *));
    if (map->arena == NULL)
        return NULL;
    for (size_t i = 0; i < y; i++) {
        map->arena[i] = calloc(x + 1, sizeof(struct tile_s));
        if (map->arena[i] == NULL)
            return NULL;
    }
    return map;
}

static void fill_food(map_t *map, size_t number)
{
    int x = 0;
    int y = 0;

    for (size_t i = 0; i < number; i++) {
        x = rand() % map->x;
        y = rand() % map->y;
        map->arena[y][x].content.food += 1;
    }
}

void fill_map(map_t *map)
{
    fill_food(map, map->x * map->y * FOOD_DENSITY);
}
