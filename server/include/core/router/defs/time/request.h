/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** request
*/

#pragma once

#pragma once

#include "core/gui/defs.h"
#include "core/router/route.h"

static const route_t REQUEST_ROUTE = {
    .args = 0,
    .command = "sgt",
    .f = &request_time,
    .mode = GUI,
    .time = 0,
};
