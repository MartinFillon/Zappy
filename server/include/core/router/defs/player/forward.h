/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** forward
*/

#pragma once

#include "core/ai/defs.h"
#include "core/router/route.h"

static const route_t FORWARD_ROUTE = {
    .args = 0,
    .command = "Forward",
    .f = &handle_forward,
    .mode = AI,
    .time = 7,
};
