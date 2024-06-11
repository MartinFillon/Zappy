/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** events
*/

#pragma once

#include <raylib.h>
#include "dashboard/internal.h"

struct key_event {
    int key;
    void (*f)(struct draw_state_s *);
};

#define REGISTER_EVENT(name) void handle_##name(struct draw_state_s *st)

REGISTER_EVENT(left_key);
REGISTER_EVENT(right_key);

static const struct key_event KEY_EVENTS[] = {
    {
        KEY_LEFT,
        handle_left_key,
    },
    {
        KEY_RIGHT,
        handle_right_key,
    },
    {
        0,
        NULL,
    }
};
