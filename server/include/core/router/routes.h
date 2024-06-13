/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** routes
*/

#pragma once

#include "route.h"

#include "defs/map/content.h"
#include "defs/map/size.h"
#include "defs/map/tile.h"
#include "defs/player/broadcast.h"
#include "defs/player/eject.h"
#include "defs/player/fork.h"
#include "defs/player/forward.h"
#include "defs/player/incantation.h"
#include "defs/player/inventory.h"
#include "defs/player/level.h"
#include "defs/player/look.h"
#include "defs/player/position.h"
#include "defs/player/rotate.h"
#include "defs/time/request.h"
#include "defs/time/update.h"
#include "defs/player/connect_nbr.h"
#include "defs/player/set_object.h"
#include "defs/player/take_object.h"
#include "defs/team_names.h"

#define BASE_ROUTE_COUNT 23

// clang-format off
static const route_t ROUTES[BASE_ROUTE_COUNT] = {
    CONTENT_ROUTE,
    TILE_CONTENT_ROUTE,
    SIZE_ROUTE,
    TILE_ROUTE,
    REQUEST_ROUTE,
    UPDATE_ROUTE,
    INVENTORY_ROUTE,
    LEVEL_ROUTE,
    POSITION_ROUTE,
    TEAM_NAMES_ROUTE,
    FORWARD_ROUTE,
    ROTATE_RIGHT_ROUTE,
    ROTATE_LEFT_ROUTE,
    LOOK_ROUTE,
    BROADCAST_ROUTE,
    SET_OBJECT_ROUTE,
    TAKE_OBJECT_ROUTE,
    FORK_ROUTE,
    CONNECT_NBR_ROUTE,
    EJECT_ROUTE,
    PLAYER_INVENTORY_ROUTE,
    START_INCANTATION,
    END_INCANTATION
};
