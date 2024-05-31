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
        logs(INFO, "command: %s\n", this->data[i]->command->data);
        if (str_cmp(this->data[i]->command, name) == 0 &&
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
        return INVALID_ARGS_CALLBACKS[cli->type](cli->fd);
    }
    route->f(cli, &state);
}

void run_router(
    struct router const *this,
    client_t *cli,
    zappy_t *zappy,
    str_t *line
)
{
    struct vector_str_t *v = str_split(line, " \t");
    route_t *route = NULL;

    if (v->size == 0)
        return;
    route = get_route(this, v->data[0], cli->type);
    if (route == NULL)
        UNKNOWN_CALLBACKS[cli->type](2);
    else
        run_callback(cli, zappy, route, v);
    vec_free_vector_str_t(v, &str_free);
}
