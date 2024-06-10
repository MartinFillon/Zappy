/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** initializer
*/

#include <stdlib.h>

#include "macros.h"
#include "map.h"
#include "types/map.h"
#include "types/object.h"

static void init_tile(struct tile_s *tile)
{
    tile->content = calloc(OBJ_COUNT, sizeof(size_t));
    tile->players = vec_create_vector_int(10);
}

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
    for (size_t i = 0; i < y; i++) {
        for (size_t j = 0; j < x; j++)
            init_tile(&map->arena[i][j]);
    }
    return map;
}

static size_t count_obj(map_t *const map, enum object_e obj)
{
    size_t c = 0;

    for (size_t y = 0; y < map->y; y++)
        for (size_t x = 0; x < map->x; x++)
            c += map->arena[y][x].content[obj];
    return c;
}

static void put_on_tile(map_t *map, enum object_e obj)
{
    size_t x = rand() % map->x;
    size_t y = rand() % map->y;

    if (map->arena[y][x].content[obj] >= 1)
        return put_on_tile(map, obj);
    map->arena[y][x].content[obj] = 1;
}

static void fill_tiles(map_t *map, double min, enum object_e obj)
{
    size_t c = count_obj(map, obj);
    size_t to_add = (c < min) ? min - c : 0;

    for (; to_add > 0; to_add--)
        put_on_tile(map, obj);
}

void fill_map(map_t *map)
{
    fill_tiles(map, map->x * map->y * FOOD_DENSITY, FOOD);
    fill_tiles(map, map->x * map->y * LINEMATE_DENSITY, LINEMATE);
    fill_tiles(map, map->x * map->y * DERAUMERE_DENSITY, DERAUMERE);
    fill_tiles(map, map->x * map->y * SIBUR_DENSITY, SIBUR);
    fill_tiles(map, map->x * map->y * MENDIANE_DENSITY, MENDIANE);
    fill_tiles(map, map->x * map->y * PHIRAS_DENSITY, PHIRAS);
    fill_tiles(map, map->x * map->y * THYSTAME_DENSITY, THYSTAME);
}
