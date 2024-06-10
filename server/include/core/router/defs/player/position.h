/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** position
*/

#pragma once

#include "core/gui/defs.h"
#include "core/router/route.h"

static const route_t POSITION_ROUTE = {
    .args = 1,
    .command = "ppo",
    .f = &player_position,
    .mode = GUI,
    .time = 0,
};
