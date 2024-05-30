/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** callbacks
*/

#pragma once

// #include "gui/defs.h"
#include "router/route.h"
#include "types/client.h"
#include "types/game.h"

struct callback_map_s {
    char *const name;
    callback_t f;
};

void placeholder(
    char *,
    client_t *,
    game_t *,
    client_t const *
);

static const struct callback_map_s CALLBACKS[] = {
    {"map_size", &placeholder},
    {"map_content_tile", &placeholder},
    {"map_content_full", &placeholder},
    {"team_names", &placeholder},
    {"player_position", &placeholder},
    {"player_level", &placeholder},
    {"player_inventory", &placeholder},
    {"request_time", &placeholder},
    {"update_time", &placeholder},
    {NULL, NULL},
};
