/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** inventory
*/

#pragma once

#include "gui/defs.h"
#include "router/route.h"

static const route_t INVENTORY_ROUTE = {
    .args = 1,
    .command = "pin",
    .f = &player_inventory,
    .mode = GUI,
    .time = 0,
};
