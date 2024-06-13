/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** router
*/

#pragma once

#include "core/router/route.h"
#include "core/types/client.h"
#include "str.h"
#include "zappy.h"

#define TYPE route_t *
#define NAME router
#include "vector.h"

typedef struct router_s {
    struct router *self;
} router_t;

/**
 * @brief Initialize a new router
 *
 * @return router_t* The new router allocated
 */
router_t *init_router(void);

/**
 * @brief Destroys a router
 * @param router The router to destroy
 */
void destroy_router(router_t *router);

/**
 * @brief Runs the router against a line
 * @param this The router
 * @param cli The client
 * @param zappy The zappy
 * @param line The line to run
 */
void run_router(
    router_t const *this,
    client_t *cli,
    zappy_t *zappy,
    str_t *line
);

/**
 * @brief The router for when a client doesn't have a type
 * @param c The client
 * @param s The command state
 */
void unset_command(client_t *c, command_state_t *s);
