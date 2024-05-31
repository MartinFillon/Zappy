/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** router
*/

#pragma once

#include "route.h"
#include "zappy.h"

#define TYPE route_t *
#define NAME router
#include "vector.h"

typedef struct router_s {
    struct router *self;
    str_t *routes_path;
} router_t;

void destroy_router(router_t *router);
int load_route(struct router *routes, str_t const *file);
router_t *init_router(char const *file);
void destroy_router(router_t *router);
void run_router(
    router_t const *this,
    client_t *cli,
    zappy_t *zappy,
    str_t *line
);
