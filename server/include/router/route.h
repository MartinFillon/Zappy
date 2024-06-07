/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** route
*/

#pragma once

#include "types/client.h"
#include "types/game.h"

typedef struct {
    struct vector_str_t *args;
    struct client_list *clients;
    game_t *game;
} command_state_t;

typedef void (*callback_t)(client_t *, command_state_t *);

typedef struct {
    char *command;
    double time;
    enum client_type_e mode;
    callback_t f;
    size_t args;
} route_t;

#define DECLARE_ROUTE(name) void name(client_t *, command_state_t *)

enum client_type_e get_mode(char const *mode);
callback_t get_callback(char const *name);
