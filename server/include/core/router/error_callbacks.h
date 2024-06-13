/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** error_callbacks
*/

#pragma once

#include "core/client.h"
#include "core/types/client.h"

typedef void (*unknown_route_callback_t)(client_t *);
typedef void (*invalid_args_callback_t)(client_t *);

/**
 * @brief Callback for unknown route on gui clients
 * @param c the client
 */
static inline void gui_unknown_route(client_t *c)
{
    prepare_response_cat(&c->io, "suc\n");
}

/**
 * @brief Callback for unknown route on default clients
 * @param c the client
 */
static inline void default_unknown_route(client_t *c)
{
    prepare_response_cat(&c->io, "ko\n");
}

/**
 * @brief Callback for invalid args on default clients
 * @param c the client
 */
static inline void default_invalid_args(client_t *c)
{
    prepare_response_cat(&c->io, "ko\n");
}

/**
 * @brief Callback for invalid args on gui clients
 * @param c the client
 */
static inline void gui_invalid_args(client_t *c)
{
    prepare_response_cat(&c->io, "sbp\n");
}

static const unknown_route_callback_t UNKNOWN_CALLBACKS[3] = {
    default_unknown_route,
    default_unknown_route,
    gui_unknown_route,
};

static const invalid_args_callback_t INVALID_ARGS_CALLBACKS[3] = {
    default_invalid_args,
    default_invalid_args,
    gui_invalid_args,
};
