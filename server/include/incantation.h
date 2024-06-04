/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** incantation
*/

#pragma once

#include "types/map.h"

typedef struct tile_content_s ressource_require_t;

typedef struct incant_require_s {
    size_t level;
    size_t nb_player;
    ressource_require_t ressource;
} incant_require_t;

static const incant_require_t incant_req[] = {
    {1, 1, {0, 1, 0, 0, 0, 0, 0}},
    {2, 2, {0, 1, 1, 1, 0, 0, 0}},
    {3, 2, {0, 2, 0, 1, 0, 2, 0}},
    {4, 4, {0, 1, 1, 2, 0, 1, 0}},
    {5, 4, {0, 1, 2, 1, 3, 0, 0}},
    {6, 6, {0, 1, 2, 3, 0, 1, 0}},
    {7, 6, {0, 2, 2, 2, 2, 2, 1}}
};
