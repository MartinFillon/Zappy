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
#include "map.h"

enum client_type_e {
    UNSET,
    AI,
    GUI,
};

struct buffer_s {
    char *buffer;
    size_t size;
};

typedef struct {
    ai_t *ais;
    map_t *map;
    char **teams;
    size_t ai_count;
} game_t;

typedef struct client_s {
    int fd;
    struct buffer_s buffer;
    ai_t *ai; // only for AI clients
    enum client_type_e type;
    int (*entrypoint)(char const *, struct client_s *, game_t *);
} client_t;
