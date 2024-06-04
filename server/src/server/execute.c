/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** execute
*/

#include "clock.h"
#include "router/router.h"
#include "server.h"
#include "types/client.h"
#include "zappy.h"

static void case_ai(zappy_t *z, client_t *c)
{
    if (has_n_ticks_passed(c->ai->clock, c->ai->cycles_to_wait)) {
        run_router(
            z->server.router, c, z, queue_pop_queue_command_t(c->commands)
        );
    }
}

void execute_commands(zappy_t *z)
{
    for (__auto_type i = 0; i < SOMAXCONN; i++) {
        if (z->clients[i].fd <= 0 || z->clients[i].commands->size == 0)
            continue;
        if (z->clients[i].type == UNSET || z->clients[i].type == GUI) {
            run_router(
                z->server.router,
                &z->clients[i],
                z,
                queue_pop_queue_command_t(z->clients[i].commands)
            );
        }
        if (z->clients[i].type == AI)
            case_ai(z, &z->clients[i]);
    }
}
