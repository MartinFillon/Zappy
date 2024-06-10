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

struct tile_s {
    struct vector_int *players;

    size_t *content;
};

typedef struct {
    size_t x;
    size_t y;

    struct tile_s **arena;
} map_t;
