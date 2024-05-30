/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** router
*/

#pragma once

#include "route.h"

#define TYPE route_t *
#define NAME router
#include "vector.h"

void destroy_router(struct router *router);
int load_route(struct router *routes, str_t const *file);
struct router *init_router(char const *file);
void destroy_router(struct router *router);
void run_router(enum client_type_e cli, struct router const *r, str_t *line);
