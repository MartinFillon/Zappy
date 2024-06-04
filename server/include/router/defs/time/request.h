/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** request
*/

#pragma once

#pragma once

#include "gui/defs.h"
#include "router/route.h"

static const route_t REQUEST_ROUTE = {
    .args = 0,
    .command = "sst",
    .f = &request_time,
    .mode = GUI,
    .time = 0,
};
