/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** update
*/

#pragma once

#pragma once

#include "gui/defs.h"
#include "router/route.h"

static const route_t UPDATE_ROUTE = {
    .args = 1,
    .command = "sst",
    .f = &update_time,
    .mode = GUI,
    .time = 0,
};
