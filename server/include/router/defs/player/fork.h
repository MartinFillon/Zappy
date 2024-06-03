/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** fork
*/

#pragma once

#include "ai/defs.h"
#include "router/route.h"

static const route_t FORK_ROUTE = {
    .args = 0,
    .command = "Fork",
    .f = &handle_fork,
    .mode = AI,
    .time = 42,
};
