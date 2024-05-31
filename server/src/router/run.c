/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** run
*/

#include <stdio.h>

#include "logger.h"
#include "router/router.h"
#include "types/client.h"
#include "zappy.h"
#include "router/error_callbacks.h"

static route_t *get_route(
    struct router const *this,
    str_t *name,
    enum client_type_e cli_mode
)
{
    for (__auto_type i = 0ul; i < this->size; i++) {
        if (strcmp(this->data[i]->command, name->data) == 0 &&
            this->data[i]->mode == cli_mode)
            return this->data[i];
    }
    return NULL;
}

static void run_callback(
    client_t *cli,
    zappy_t *zappy,
    route_t *route,
    struct vector_str_t *line
)
{
    command_state_t state = {
        .args = line,
        .clients = zappy->clients,
        .game = &zappy->game,
    };

    if (route->args + 1 != line->size) {
        return INVALID_ARGS_CALLBACKS[cli->type](cli);
    }
    route->f(cli, &state);
}

void run_router(
    router_t const *this,
    client_t *cli,
    zappy_t *zappy,
    str_t *line
)
{
    struct vector_str_t *v = str_split(line, " \t");
    route_t *route = {0};
    static route_t unset = {NULL, 0, UNSET, &unset_command, 0};

    if (v->size == 0)
        return;
    if (cli->type != UNSET)
        route = get_route(this->self, v->data[0], cli->type);
    else
        route = &unset;
    if (route == NULL)
        UNKNOWN_CALLBACKS[cli->type](cli);
    else
        run_callback(cli, zappy, route, v);
    vec_free_vector_str_t(v, &str_free);
}
