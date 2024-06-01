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

static const route_t TEAM_NAMES_ROUTE = {
    .args = 0,
    .command = "tna",
    .f = &team_names,
    .mode = GUI,
    .time = 0,
};
