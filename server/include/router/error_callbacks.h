/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** error_callbacks
*/

#pragma once

#include <stdio.h>

typedef void (*unknown_route_callback_t)(int);

static inline void gui_unknown_route(int fd)
{
    dprintf(fd, "sbp\n");
}

static inline void default_unknown_route(int fd)
{
    dprintf(fd, "ko\n");
}

static const unknown_route_callback_t UNKNOWN_CALLBACKS[3] = {
    default_unknown_route,
    gui_unknown_route,
    gui_unknown_route,
};

typedef void (*invalid_args_callback_t)(int);

static inline void default_invalid_args(int fd)
{
    dprintf(fd, "ko\n");
}

static const invalid_args_callback_t INVALID_ARGS_CALLBACKS[3] = {
    default_invalid_args,
    default_invalid_args,
    default_invalid_args,
};
