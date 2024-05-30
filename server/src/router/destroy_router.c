/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** destroy_router
*/

#include "router/router.h"
#include "utils.h"

static void delete_route(route_t **route)
{
    va_free(
        5,
        (*route)->name->data,
        (*route)->name,
        (*route)->description,
        (*route)->description->data,
        (*route)
    );
}

void destroy_router(struct router *router)
{
    vec_foreach_router(router, delete_route);
    vec_destroy_router(router);
}
