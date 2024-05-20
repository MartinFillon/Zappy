/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client
*/

#pragma once

#include <stdlib.h>

typedef struct {
    char *team;
    size_t x;
    size_t y;
} ai_t;

enum client_type_e {
    AI,
    GUI,
    UNSET,
};

typedef struct {
    size_t map_x;
    size_t map_y;

    size_t nb_teams;
    ai_t *ais;
} game_t;

union data_u {
    ai_t *ai;
    game_t *gui;
};

typedef struct {
    char *str;
    size_t len;
} buffer_t;

typedef struct {
    int fd;
    buffer_t *buffer;
    union data_u data;
    enum client_type_e type;
    int (*fct)(int, char const *, union data_u *data, game_t *game);
} client_t;
