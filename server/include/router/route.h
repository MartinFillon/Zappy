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

typedef void (*callback_t)(char *, client_t *, game_t *, client_t const *);

typedef struct {
    str_t *name;
    str_t *description;
    double time;
    enum client_type_e mode;
    callback_t f;
} route_t;

#define TYPE route_t *
#define NAME router
#include "vector.h"

enum client_type_e get_mode(char const *mode);
callback_t get_callback(char const *name);
