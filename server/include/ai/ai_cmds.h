/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai_cmds
*/

#pragma once

#include <stdlib.h>
#include "types/client.h"

typedef struct ai_cmds_s {
    char const *name;
    int (*func)(client_t *, game_t *);
} ai_cmds_t;

int handle_forward(client_t *cli, game_t *game);

static const ai_cmds_t AI_CMDS[] = {
    {"Forward", handle_forward},

    // {"Right", NULL},
    // {"Left", NULL},

    // {"Look", NULL},
    // {"Inventory", NULL},
    // {"Broadcast text", NULL},

    // {"Connect_nbr", NULL},
    // {"Fork", NULL},
    // {"Eject", NULL},

    // {"Take object", NULL},
    // {"Set object", NULL},
    // {"Incantation", NULL},

    {NULL, NULL}
};
