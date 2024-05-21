/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** map
*/

#pragma once

#include <stdbool.h>
#include <stdlib.h>

struct tile_s {
    bool occupied;

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
