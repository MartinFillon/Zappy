/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_broadcast
*/

#include <sys/socket.h>

#include "utils.h"
#include "types/client.h"
#include "client.h"

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

void handle_broadcast(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
)
{
    struct vector_ai_t *ais = game->ais;

    (void) clients;
    (void) ais;
    if (is_empty(arg))
        return prepare_response(&cli->io, "ko\n");
    prepare_response(&cli->io, "ok\n");
    send_to_everyone(arg, clients, cli);
}
