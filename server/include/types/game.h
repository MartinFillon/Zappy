/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#pragma once

#include <stddef.h>
#include "types/ai.h"
#include "types/team.h"

typedef struct {
    ai_t *ais;
    size_t len;
    size_t size;
} vector_ai_t;

typedef struct {
    vector_ai_t *ais;
    map_t *map;
    teams_t *teams;
    long frequency;
} game_t;
