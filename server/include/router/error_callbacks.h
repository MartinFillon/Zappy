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

static inline void ai_unknown_route(int fd)
{
    dprintf(fd, "ko\n");
}

static inline void default_unknown_route(int fd)
{
    dprintf(fd, "ko\n");
}

static const unknown_route_callback_t UNKNOWN_CALLBACKS[3] = {
    gui_unknown_route,
    ai_unknown_route,
    default_unknown_route,
};
