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
#include "types/ai.h"
#include "types/client.h"
#include "types/object.h"

static void send_death(int n, struct client_list *clients)
{
    for (size_t i = 0; i < clients->size; i++) {
        if (clients->data[i].type == GUI) {
            prepare_response_cat(&clients->data[i].io, "edi %d\n", n);
        }
    }
}

void make_ai_eat(client_t *cli, struct client_list *clients, int n)
{
    if (!cli->ai->alive || !has_n_ticks_passed(cli->ai->food_clock, 126))
        return;
    if (cli->ai->inventory[FOOD] == 0) {
        logs(INFO, "Ai %d is dead\n", n);
        prepare_response_cat(&cli->io, "dead\n");
        send_death(n, clients);
        cli->ai->alive = false;
    }
    logs(INFO, "Cli %d is eating\n", n);
    cli->ai->inventory[FOOD] -= 1;
    reset_clock(cli->ai->food_clock);
}
