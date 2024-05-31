/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client
*/

#pragma once

#include <stdbool.h>

#include "ai.h"
#include "types/buffer.h"
#include "types/game.h"

enum client_type_e {
    UNSET,
    AI,
    GUI,
};

typedef struct client_s {
    int fd;
    io_t io;
    ai_t *ai; // only for AI clients
    enum client_type_e type;
} client_t;
