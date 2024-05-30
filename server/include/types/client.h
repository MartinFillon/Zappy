/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client
*/

#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "ai.h"
#include "types/game.h"

enum client_type_e {
    UNSET,
    AI,
    GUI,
};

struct buffer_s {
    char *buffer;
    size_t size;
};

// Next step is putting a queue on request
typedef struct io_s {
    struct buffer_s req;
    struct buffer_s res;
    bool is_ready;
} io_t;

typedef struct client_s {
    int fd;
    io_t io;
    ai_t *ai; // only for AI clients
    enum client_type_e type;
    int (*entrypoint)(
        char const *,
        struct client_s *,
        game_t *,
        struct client_s *
    );
} client_t;
