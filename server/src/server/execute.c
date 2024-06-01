/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** execute
*/

#include "clock.h"
#include "router/router.h"
#include "types/client.h"
#include "zappy.h"

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
        if (z->clients[i].type == AI &&
            has_n_ticks_passed(
                z->clients[i].ai->clock, z->clients[i].ai->cycles_to_wait
            )) {
            run_router(
                z->server.router,
                &z->clients[i],
                z,
                queue_pop_queue_command_t(z->clients[i].commands)
            );
        }
    }
}
