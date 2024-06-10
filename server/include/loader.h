/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** loader
*/

#pragma once

#include "server.h"

typedef struct {
    bool (*loop)(zappy_t *);
    void *handle;
} lib_t;
