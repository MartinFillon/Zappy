/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** set_object
*/

#pragma once

#include "core/ai/defs.h"
#include "core/router/route.h"

static const route_t SET_OBJECT_ROUTE = {
    .args = 1,
    .command = "Set",
    .f = &handle_set_object,
    .mode = AI,
    .time = 7,
};
