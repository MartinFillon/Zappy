/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** displayers
*/

#pragma once

#include "core/types/ai.h"

typedef void (*displayer_t)(ai_t *data, int x, int y);

#define REGISTER_DISPLAYER(name) void display_##name(ai_t *data, int x, int y)

REGISTER_DISPLAYER(team);
REGISTER_DISPLAYER(inventory);
REGISTER_DISPLAYER(id);
REGISTER_DISPLAYER(level);

static const displayer_t displayers[] = {
    display_id,
    display_team,
    display_level,
    // display_inventory,
    NULL,
};
