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

void destroy_router(struct router *router);
int load_route(struct router *routes, str_t const *file);
struct router *init_router(char const *file);
void destroy_router(struct router *router);
void run_router(
    struct router const *this,
    client_t *cli,
    zappy_t *zappy,
    str_t *line
);
