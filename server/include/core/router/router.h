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

void destroy_router(router_t *router);
router_t *init_router(void);
void destroy_router(router_t *router);
void run_router(
    router_t const *this,
    client_t *cli,
    zappy_t *zappy,
    str_t *line
);
void unset_command(client_t *c, command_state_t *s);
