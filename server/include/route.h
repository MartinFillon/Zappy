/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** route
*/

#pragma once

#include "str.h"
#include "types/client.h"
#include "types/game.h"

typedef struct {
    str_t *name;
    str_t *description;
    double time;
    enum client_type_e mode;
    void (*f)(
        char const *restrict,
        client_t *restrict,
        game_t *restrict,
        client_t const *restrict
    );
} route_t;

#define TYPE route_t *
#define NAME router
#include "vector.h"

enum client_type_e get_mode(char const *restrict mode);
