/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** broadcast
*/

#pragma once

#include "ai/defs.h"
#include "router/route.h"

static const route_t BROADCAST_ROUTE = {
    .args = 1,
    .command = "Broadcast",
    .f = &handle_broadcast,
    .mode = AI,
    .time = 7,
};
