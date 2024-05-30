/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** eat
*/

#include <sys/socket.h>

#include "client.h"
#include "clock.h"
#include "logger.h"
#include "server.h"
#include "types/ai.h"
#include "types/ai.h"
#include "types/client.h"
#include "utils.h"

static void send_death(int n, client_t *clients)
{
    for (__auto_type i = 0; i < SOMAXCONN; i++) {
        if (clients[i].fd > 0 && clients[i].type == GUI) {
            send_client(&clients[i], "edi %d\n", n);
        }
    }
}

void make_ai_eat(client_t *cli, client_t *clients, int n)
{
    if (!cli->ai->alive || !has_n_ticks_passed(cli->ai->food_clock, 126)) {
        return;
    }
    if (cli->ai->inventory.food == 0) {
        logs(INFO, "Ai %d is dead\n", n);
        send_client(cli, "dead\n");
        send_death(n, clients);
    }
    logs(INFO, "Cli %d is eating\n", n);
    cli->ai->inventory.food -= 1;
    reset_clock(cli->ai->food_clock);
    cli->ai->alive = false;
}
