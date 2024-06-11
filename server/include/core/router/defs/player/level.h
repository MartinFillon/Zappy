/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** level
*/

#pragma once

#include "core/gui/defs.h"
#include "core/router/route.h"

static const route_t LEVEL_ROUTE = {
    .args = 1,
    .command = "plv",
    .f = &player_level,
    .mode = GUI,
    .time = 0,
};
