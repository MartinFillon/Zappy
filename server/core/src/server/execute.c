/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** execute
*/

#include "core/clock.h"
#include "core/router/router.h"
#include "core/server.h"
#include "core/types/client.h"
#include "logger.h"
#include "zappy.h"

static void case_ai(zappy_t *z, client_t *c)
{
    if (has_n_ticks_passed(c->ai->clock, c->ai->cycles_to_wait) &&
        c->commands->size > 0) {
        run_router(
            z->server.router, c, z, queue_pop_queue_command_t(c->commands)
        );
    }
}

void execute_commands(zappy_t *z)
{
    for (size_t i = 0; i < z->clients->size; i++) {
        if (z->clients->data[i].commands->size == 0)
            continue;
        logs(
            DEBUG, "client com count: %d\n", z->clients->data[i].commands->size
        );
        if (z->clients->data[i].type == UNSET ||
            z->clients->data[i].type == GUI) {
            run_router(
                z->server.router,
                &z->clients->data[i],
                z,
                queue_pop_queue_command_t(z->clients->data[i].commands)
            );
        }
        if (z->clients->data[i].type == AI)
            case_ai(z, &z->clients->data[i]);
    }
}
