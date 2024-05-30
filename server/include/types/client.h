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

enum client_type_e {
    UNSET,
    AI,
    GUI,
};

struct buffer_s {
    char *buffer;
    size_t size;
};

typedef struct io_s {
    struct buffer_s req;
    struct buffer_s res;
    bool is_ready;
} io_t;

typedef struct client_s {
    int fd;
    struct buffer_s buffer;
    ai_t *ai;
    enum client_type_e type;
} client_t;
