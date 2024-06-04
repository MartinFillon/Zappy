/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** destroy_router
*/

#include "router/router.h"

static void delete_route(route_t **route)
{
    free((*route));
}

void destroy_router(router_t *router)
{
    vec_foreach_router(router->self, delete_route);
    vec_destroy_router(router->self);
    free(router);
}
