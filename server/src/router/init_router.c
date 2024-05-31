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

static str_t *get_path(str_t const *name)
{
    str_t *path = str_snew("server/config/router/");

    str_sadd(path, name);
    str_scadd(path, ".json");
    return path;
}

static void load_routes(struct vec_json_t *routes, struct router *router)
{
    str_t *current = NULL;

    if (!routes)
        return logs(ERROR_LEVEL, "Failed to load routes\n");
    for (size_t i = 0; i < routes->size; i++) {
        if (routes->data[i]->t != STRING)
            continue;
        current = get_path(routes->data[i]->data.str);
        if (!current)
            continue;
        logs(INFO, "current: %s\n", current->data);
        if (load_route(router, current) == ERROR)
            logs(ERROR_LEVEL, "Failed to load route\n");
        va_free(2, current->data, current);
    }
}

struct router *init_router(char const *file)
{
    struct router *router = vec_create_router(10);
    json_data_t *json = json_from_file(file);
    str_t *route_key = str_snew("routes");

    if (!json || !router) {
        logs(ERROR_LEVEL, "ROUTER INIT ERROR\n");
        return NULL;
    }
    load_routes(json_get_array(json, route_key), router);
    logs(INFO, "Router successfully inited\n");
    va_free(2, route_key->data, route_key);
    json_free(json);
    return router;
}
