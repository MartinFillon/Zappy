/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** routes
*/

#pragma once

#include "route.h"

#define BASE_ROUTE_COUNT 9

#include "defs/map/content.h"
#include "defs/map/size.h"
#include "defs/map/tile.h"
#include "defs/player/inventory.h"
#include "defs/player/level.h"
#include "defs/player/position.h"
#include "defs/time/request.h"
#include "defs/time/update.h"
#include "defs/team_names.h"

static const route_t ROUTES[9] = {
    CONTENT_ROUTE,
    SIZE_ROUTE,
    TILE_ROUTE,
    REQUEST_ROUTE,
    UPDATE_ROUTE,
    INVENTORY_ROUTE,
    LEVEL_ROUTE,
    POSITION_ROUTE,
    TEAM_NAMES_ROUTE,
};
