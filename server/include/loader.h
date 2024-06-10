/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** loader
*/

#pragma once

#include "core/server.h"

typedef struct {
    bool (*loop)(zappy_t *, void *);
    void *(*init)(void);
    void *handle;
} lib_t;

lib_t open_dhl(char const *file);
void close_dhl(lib_t *l);
