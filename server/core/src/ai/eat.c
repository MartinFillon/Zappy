/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** eat
*/

#include <sys/socket.h>

#include "core/client.h"
#include "core/clock.h"
#include "core/types/ai.h"
#include "core/types/client.h"
#include "core/types/object.h"
#include "logger.h"

static void send_death(int n, struct client_list *clients)
{
    for (size_t i = 0; i < clients->size; i++) {
        if (clients->data[i]->type == GUI) {
            prepare_response_cat(&clients->data[i]->io, "edi %d\n", n);
        }
    }
}

void make_ai_eat(client_t *cli, struct client_list *clients)
{
    if (cli->ai->godmode || !cli->ai->alive ||
        !has_n_ticks_passed(cli->ai->food_clock, 126))
        return;
    logs(
        DEBUG,
        "Client %d Ai %d has %d food\n",
        cli->fd,
        cli->ai->id,
        cli->ai->inventory[FOOD]
    );
    if (cli->ai->inventory[FOOD] == 0) {
        logs(INFO, "Client %d Ai %d is dead\n", cli->fd, cli->ai->id);
        prepare_response_cat(&cli->io, "dead\n");
        send_death(cli->ai->id, clients);
        cli->ai->alive = false;
        return;
    }
    logs(INFO, "Client %d AI %d is eating\n", cli->fd, cli->ai->id);
    cli->ai->inventory[FOOD] -= 1;
    reset_clock(cli->ai->food_clock);
}
