/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** eject
*/

#pragma once

#include "core/ai/defs.h"
#include "core/router/route.h"

static const route_t EJECT_ROUTE = {
    .args = 0,
    .command = "Eject",
    .f = &handle_eject,
    .mode = AI,
    .time = 7,
};
