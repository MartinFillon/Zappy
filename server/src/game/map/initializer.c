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
            map->arena[i][j].players = vec_create_vector_int(10);
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

static void fill_deraumere(map_t *map, size_t number)
{
    int x = 0;
    int y = 0;

    for (size_t i = 0; i < number; i++) {
        x = rand() % map->x;
        y = rand() % map->y;
        map->arena[y][x].content.deraumere += 1;
    }
}

static void fill_linemate(map_t *map, size_t number)
{
    int x = 0;
    int y = 0;

    for (size_t i = 0; i < number; i++) {
        x = rand() % map->x;
        y = rand() % map->y;
        map->arena[y][x].content.linemate += 1;
    }
}

static void fill_sibur(map_t *map, size_t number)
{
    int x = 0;
    int y = 0;

    for (size_t i = 0; i < number; i++) {
        x = rand() % map->x;
        y = rand() % map->y;
        map->arena[y][x].content.sibur += 1;
    }
}

static void fill_mendiane(map_t *map, size_t number)
{
    int x = 0;
    int y = 0;

    for (size_t i = 0; i < number; i++) {
        x = rand() % map->x;
        y = rand() % map->y;
        map->arena[y][x].content.mendiane += 1;
    }
}

static void fill_phiras(map_t *map, size_t number)
{
    int x = 0;
    int y = 0;

    for (size_t i = 0; i < number; i++) {
        x = rand() % map->x;
        y = rand() % map->y;
        map->arena[y][x].content.phiras += 1;
    }
}

static void fill_thystame(map_t *map, size_t number)
{
    int x = 0;
    int y = 0;

    for (size_t i = 0; i < number; i++) {
        x = rand() % map->x;
        y = rand() % map->y;
        map->arena[y][x].content.thystame += 1;
    }
}

void fill_map(map_t *map)
{
    fill_food(map, map->x * map->y * FOOD_DENSITY);
    fill_deraumere(map, map->x * map->y * DERAUMERE_DENSITY);
    fill_linemate(map, map->x * map->y * LINEMATE_DENSITY);
    fill_mendiane(map, map->x * map->y * MENDIANE_DENSITY);
    fill_sibur(map, map->x * map->y * SIBUR_DENSITY);
    fill_phiras(map, map->x * map->y * PHIRAS_DENSITY);
    fill_thystame(map, map->x * map->y * THYSTAME_DENSITY);
}
