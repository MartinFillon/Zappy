/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** rotate
*/

#pragma once

#include "core/ai/defs.h"
#include "core/router/route.h"

static const route_t ROTATE_RIGHT_ROUTE = {
    .args = 0,
    .command = "Right",
    .f = &handle_rotate_right,
    .mode = AI,
    .time = 7,
};

static const route_t ROTATE_LEFT_ROUTE = {
    .args = 0,
    .command = "Left",
    .f = &handle_rotate_left,
    .mode = AI,
    .time = 7,
};
