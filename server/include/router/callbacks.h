/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** callbacks
*/

#pragma once

#include "gui/defs.h"
#include "router/route.h"
#include "types/client.h"

struct callback_map_s {
    char *const name;
    callback_t f;
};

void placeholder(client_t *, command_state_t *);

static const struct callback_map_s CALLBACKS[] = {
    {"map_size", &map_size},
    {"map_content_tile", &map_content_tile},
    {"map_content_full", &map_content_full},
    {"team_names", &team_names},
    {"player_position", &player_position},
    {"player_level", &player_level},
    {"player_inventory", &player_inventory},
    {"request_time", &request_time},
    {"update_time", &update_time},
    {NULL, NULL},
};
