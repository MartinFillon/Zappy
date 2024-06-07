/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#pragma once

#include <stddef.h>
#include "types/clock.h"
#include "types/map.h"

#include "types/ai.h"
#define TYPE ai_t
#include "vector.h"

#include "types/team.h"

#define TYPE team_t
#include "vector.h"

typedef struct {
    struct vector_ai_t *ais;
    map_t *map;
    struct vector_team_t *teams;
    long frequency;

    zclock_t *clock;
} game_t;
