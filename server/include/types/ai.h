/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai
*/

#pragma once

#include <stdlib.h>
#include "map.h"

#define NB_DIR 4

typedef struct tile_content_s inventory_t;

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

typedef struct pos_s {
    int x;
    int y;
} pos_t;

typedef struct {
    char *team;
    pos_t pos;
    size_t level;

    enum Direction dir;

    inventory_t inventory;
    long time_to_wait; // if current time < this time dont do anything
} ai_t;
