/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** incantation
*/

#pragma once

#include "ai/defs.h"
#include "router/route.h"

static const route_t START_ROUTE = {
    .args = 0,
    .command = "Incantation",
    .f = &handle_start_incantation,
    .mode = AI,
    .time = 300,
};

static const route_t END_ROUTE = {
    .args = 0,
    .command = "End_Incantation",
    .f = &handle_end_incantation,
    .mode = AI,
    .time = 0,
};

