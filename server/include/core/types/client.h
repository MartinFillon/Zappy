/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client
*/

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "ai.h"
#include "core/types/buffer.h"

#include "str.h"
#define TYPE str_t *
#define NAME queue_command_t
#include "queue.h"

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
    struct queue_command_t *commands;
    char *address;
    uint32_t port;
} client_t;
