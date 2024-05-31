/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** size
*/

#pragma once

#include "gui/defs.h"
#include "router/route.h"

static const route_t SIZE_ROUTE = {
    .args = 0,
    .command = "msz",
    .f = &map_size,
    .mode = GUI,
    .time = 0,
};
