/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** run
*/

#include <stdio.h>

#include "core/clock.h"
#include "core/router/route.h"
#include "core/router/router.h"
#include "core/types/client.h"
#include "logger.h"
#include "zappy.h"
#include "core/router/error_callbacks.h"

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

static void update_waiting(client_t *cli, route_t *route)
{
    if (cli->type == AI) {
        cli->ai->cycles_to_wait = route->time;
        reset_clock(cli->ai->clock);
    }
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
    update_waiting(cli, route);
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
    char *tmp = str_cstr(line);

    free(tmp);
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
    str_free(line);
}
