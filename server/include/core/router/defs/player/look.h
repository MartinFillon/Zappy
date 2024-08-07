/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** look
*/

#pragma once

#include "core/ai/defs.h"
#include "core/router/route.h"

static const route_t LOOK_ROUTE = {
    .args = 0,
    .command = "Look",
    .f = &handle_look,
    .mode = AI,
    .time = 7,
};
