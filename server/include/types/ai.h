/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai
*/

#pragma once

#include <stdlib.h>
#include "map.h"
#include "types/clock.h"
#include "types/position.h"
#include "types/team.h"

typedef struct tile_content_s inventory_t;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

typedef struct {
    team_t *team;

    pos_t pos;
    size_t level;

    enum Direction dir;

    inventory_t inventory;
    long cycles_to_wait; // if current time < this time dont do anything
    zclock_t *clock;
} ai_t;
