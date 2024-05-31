/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** error_callbacks
*/

#pragma once

#include "client.h"
#include "types/client.h"

typedef void (*unknown_route_callback_t)(client_t *);

static inline void gui_unknown_route(client_t *c)
{
    prepare_response(&c->io, "suc\n");
}

static inline void default_unknown_route(client_t *c)
{
    prepare_response(&c->io, "ko\n");
}

static const unknown_route_callback_t UNKNOWN_CALLBACKS[3] = {
    default_unknown_route,
    default_unknown_route,
    gui_unknown_route,
};

typedef void (*invalid_args_callback_t)(client_t *);

static inline void default_invalid_args(client_t *c)
{
    prepare_response(&c->io, "ko\n");
}

static inline void gui_invalid_args(client_t *c)
{
    prepare_response(&c->io, "sbp\n");
}

static const invalid_args_callback_t INVALID_ARGS_CALLBACKS[3] = {
    default_invalid_args,
    default_invalid_args,
    gui_invalid_args,
};
