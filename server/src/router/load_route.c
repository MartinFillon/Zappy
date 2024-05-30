/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** load_route
*/

#include "json/json.h"

#include "logger.h"
#include "macros.h"
#include "router/route.h"
#include "str.h"
#include "utils.h"

static int set_name(route_t *restrict route, json_data_t *restrict const json)
{
    str_t *name_key = str_snew("name");

    if (!name_key) {
        logs(ERROR_LEVEL, "Failed to allocate memory for name_key\n");
        return ERROR;
    }
    route->name = str_dup(json_get_string(json, name_key));
    if (!route->name) {
        logs(ERROR_LEVEL, "Failed to duplicate name\n");
        return ERROR;
    }
    va_free(2, name_key, name_key->data);
    return SUCCESS;
}

static int set_description(
    route_t *restrict route,
    json_data_t *restrict const json
)
{
    str_t *description_key = str_snew("description");

    if (!description_key) {
        logs(ERROR_LEVEL, "Failed to allocate memory for description_key\n");
        return ERROR;
    }
    route->description = str_dup(json_get_string(json, description_key));
    if (!route->description) {
        logs(ERROR_LEVEL, "Failed to duplicate description\n");
        return ERROR;
    }
    va_free(2, description_key, description_key->data);
    return SUCCESS;
}

static int set_mode(route_t *restrict route, json_data_t *const restrict json)
{
    str_t *mode_key = str_snew("mode");

    if (!mode_key) {
        logs(ERROR_LEVEL, "Failed to allocate memory for mode_key\n");
        return ERROR;
    }
    route->mode = get_mode(json_get_string(json, mode_key)->data);
    if (route->mode == UNSET) {
        logs(ERROR_LEVEL, "Failed to get mode\n");
        return ERROR;
    }
    va_free(2, mode_key, mode_key->data);
    return SUCCESS;
}

static int set_time(route_t *restrict route, json_data_t *restrict const json)
{
    str_t *time_key = str_snew("time");

    if (!time_key) {
        logs(ERROR_LEVEL, "Failed to allocate memory for time_key\n");
        return ERROR;
    }
    route->time = json_get_number(json, time_key);
    va_free(2, time_key, time_key->data);
    return SUCCESS;
}

static int set_callback(
    route_t *restrict route,
    json_data_t *restrict const json
)
{
    str_t *callback_key = str_snew("callback");

    if (!callback_key) {
        logs(ERROR_LEVEL, "Failed to allocate memory for callback_key\n");
        return ERROR;
    }
    route->f = get_callback(json_get_string(json, callback_key)->data);
    if (!route->f) {
        logs(ERROR, "Failed to get callback\n");
        return ERROR;
    }
    va_free(2, callback_key, callback_key->data);
    return SUCCESS;
}

int load_route(struct router *routes, char const *file)
{
    route_t *route = calloc(1, sizeof(route_t));
    json_data_t *json = json_from_file(file);
    int (*setters[5])(route_t *restrict, json_data_t *const restrict) = {
        set_name, set_description, set_mode, set_time, set_callback
    };

    if (!route || !json) {
        logs(ERROR_LEVEL, "Failed to allocate memory for route or json\n");
        return ERROR;
    }
    for (__auto_type i = 0; i < 2; i++) {
        if (setters[i](route, json) == ERROR)
            return ERROR;
    }
    vec_pushback_router(routes, route);
    json_free(json);
    return SUCCESS;
}
