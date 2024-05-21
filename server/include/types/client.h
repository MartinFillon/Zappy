/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client
*/

#pragma once

#include <stdbool.h>
#include <stdio.h>

#include "ai.h"
#include "map.h"
#include "queue.h"

enum client_type_e {
    UNSET,
    AI,
    GUI,
};

typedef struct {
    ai_t *ais;
    map_t map;
    char **teams;
} game_t;

typedef struct client_s {
    int fd;
    queue_t *process_queue;
    ai_t *ai; // only for AI clients
    enum client_type_e type;
    int (*entrypoint)(char const *, struct client_s *, game_t *);
} client_t;
