/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#pragma once

#include "types/ai.h"
#include "types/clock.h"

typedef struct {
    ai_t *ais;
    size_t ai_count;
    map_t *map;
    char **teams;
    zclock_t *clock;
} game_t;
