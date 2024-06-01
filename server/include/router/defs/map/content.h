/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** content
*/

#pragma once

#include "gui/defs.h"
#include "router/route.h"

static const route_t CONTENT_ROUTE = {
    .args = 0,
    .command = "bct",
    .f = &map_content_full,
    .mode = GUI,
    .time = 0,
};
