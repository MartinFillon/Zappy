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
    AI,
    GUI,
    UNSET = -1,
};

typedef struct {
    ai_t *ais;
    map_t map;
} game_t;

union data_u {
    ai_t *ai;
    game_t *gui;
};

typedef struct {
    int fd;
    FILE *ffd; // for getline purposes, to be openened with fdopen
    queue_t *process_queue;
    union data_u data;
    enum client_type_e type;
    int (*fct)(int, char const *, union data_u *data, map_t *game);
} client_t;
