/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** displayers
*/

#pragma once

#include "core/types/client.h"

typedef int (*displayer_t)(client_t *data, int x, int y);

#define REGISTER_DISPLAYER(name) \
    int display_##name(client_t *data, int x, int y)

REGISTER_DISPLAYER(team);
REGISTER_DISPLAYER(address);
REGISTER_DISPLAYER(inventory);
REGISTER_DISPLAYER(id);
REGISTER_DISPLAYER(level);
REGISTER_DISPLAYER(cycle);

static const displayer_t displayers[] = {
    display_id,
    display_address,
    display_team,
    display_level,
    display_cycle,
    display_inventory,
    NULL,
};
