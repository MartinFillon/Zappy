/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_router
*/

#include <string.h>
#include "logger.h"
#include "router/router.h"
#include "router/routes.h"

static void create_route(struct router *router, const route_t *route)
{
    route_t *new_route = calloc(1, sizeof(route_t));

    memcpy(new_route, route, sizeof(route_t));
    vec_pushback_router(router, new_route);
}

static void load_routes(router_t *router)
{
    for (__auto_type i = 0ul; i < BASE_ROUTE_COUNT; i++)
        create_route(router->self, &ROUTES[i]);
}

static router_t *alloc_router(void)
{
    router_t *r = calloc(1, sizeof(router_t));

    if (!r)
        return NULL;
    r->self = vec_create_router(BASE_ROUTE_COUNT);
    return r;
}

router_t *init_router(void)
{
    router_t *r = alloc_router();

    if (!r) {
        logs(ERROR_LEVEL, "ROUTER INIT ERROR\n");
        return NULL;
    }
    load_routes(r);
    logs(INFO, "Router successfully inited\n");
    return r;
}
