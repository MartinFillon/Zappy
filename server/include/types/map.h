/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map
*/

#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "vector.h"

enum object_e {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
};

struct tile_s {
    struct vector_int *players;

    struct tile_content_s {
        size_t food;
        size_t linemate;
        size_t deraumere;
        size_t sibur;
        size_t mendiane;
        size_t phiras;
        size_t thystame;
    } content;
};

typedef struct {
    size_t x;
    size_t y;

    struct tile_s **arena;
} map_t;
