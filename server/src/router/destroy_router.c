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

void destroy_router(router_t *router)
{
    vec_foreach_router(router->self, delete_route);
    vec_destroy_router(router->self);
    va_free(3, router->routes_path->data, router->routes_path, router);
}
