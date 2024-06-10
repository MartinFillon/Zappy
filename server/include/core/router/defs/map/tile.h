/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** tile
*/

#pragma once

#include "core/gui/defs.h"
#include "core/router/route.h"

static const route_t TILE_ROUTE = {
    .args = 2,
    .command = "bct",
    .f = &map_content_tile,
    .mode = GUI,
    .time = 0,
};
