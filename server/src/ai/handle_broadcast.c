/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_broadcast
*/

#include <sys/socket.h>

#include "client.h"
#include "router/route.h"
#include "types/client.h"
#include "utils.h"

static bool valid_client(client_t *to_check, client_t *banned)
{
    return to_check->fd != 0 && to_check->ai->id != banned->ai->id;
}

static void send_to_everyone(char const *msg, client_t *clients, client_t *cli)
{
    for (int i = 0; i < SOMAXCONN; i++) {
        if (valid_client(&clients[i], cli)) {
            prepare_response(&clients[i].io, "message %d, %s\n", 0, msg);
        }
    }
}

void handle_broadcast(client_t *cli, command_state_t *s)
{
    struct vector_ai_t *ais = s->game->ais;

    prepare_response(&cli->io, "ok\n");
    send_to_everyone(s->args->data[1]->data, s->clients, cli);
}
