/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#pragma once

#include <stddef.h>
#include "types/ai.h"
#include "types/clock.h"

typedef struct  {
    ai_t *ais;
    size_t len;
    size_t size;
} vector_ai_t;

typedef struct {
    vector_ai_t *ais;
    map_t *map;
    char **teams;
    zclock_t *clock;
} game_t;
