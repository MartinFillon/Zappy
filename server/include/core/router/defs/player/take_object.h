/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** take_object
*/

#pragma once

#include "core/ai/defs.h"
#include "core/router/route.h"

static const route_t TAKE_OBJECT_ROUTE = {
    .args = 1,
    .command = "Take",
    .f = &handle_take_object,
    .mode = AI,
    .time = 7,
};
