/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_router
*/

#include "json/json.h"
#include "logger.h"
#include "macros.h"
#include "router/router.h"
#include "str.h"
#include "utils.h"

static str_t *get_path(str_t const *name, str_t *const path)
{
    str_t *fpath = str_snew("server/config/");

    str_sadd(fpath, path);
    str_sadd(fpath, name);
    str_scadd(fpath, ".json");
    return fpath;
}

static void load_routes(struct vec_json_t *routes, router_t *router)
{
    str_t *current = NULL;

    if (!routes)
        return logs(ERROR_LEVEL, "Failed to load routes\n");
    for (size_t i = 0; i < routes->size; i++) {
        if (routes->data[i]->t != STRING)
            continue;
        current = get_path(routes->data[i]->data.str, router->routes_path);
        if (!current)
            continue;
        logs(INFO, "current: %s\n", current->data);
        if (load_route(router->self, current) == ERROR)
            logs(ERROR_LEVEL, "Failed to load route\n");
        va_free(2, current->data, current);
    }
}

static router_t *alloc_router(json_data_t *json)
{
    router_t *r = calloc(1, sizeof(router_t));
    str_t *path = str_snew("path");

    if (!path || !r)
        return NULL;
    r->routes_path = str_dup(json_get_string(json, path));
    if (r->routes_path == NULL)
        return NULL;
    r->self = vec_create_router(10);
    return r;
}

router_t *init_router(char const *file)
{
    json_data_t *json = json_from_file(file);
    str_t *route_key = str_snew("routes");
    router_t *r;

    if (!json) {
        logs(ERROR_LEVEL, "ROUTER INIT ERROR\n");
        return NULL;
    }
    r = alloc_router(json);
    if (!r) {
        logs(ERROR_LEVEL, "ROUTER INIT ERROR\n");
        return NULL;
    }
    load_routes(json_get_array(json, route_key), r);
    logs(INFO, "Router successfully inited\n");
    va_free(2, route_key->data, route_key);
    json_free(json);
    return r;
}
