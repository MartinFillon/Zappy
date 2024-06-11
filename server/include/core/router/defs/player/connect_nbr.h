/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** connect_nbr
*/

#pragma once

#include "core/ai/defs.h"
#include "core/router/route.h"

static const route_t CONNECT_NBR_ROUTE = {
    .args = 0,
    .command = "Connect_nbr",
    .f = &handle_connect_nbr,
    .mode = AI,
    .time = 0,
};
