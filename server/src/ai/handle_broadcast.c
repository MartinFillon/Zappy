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

static inline bool valid_client(client_t *cli1, client_t *cli2)
{
    return cli1->fd != 0 && cli1->ai->id != cli2->ai->id;
}

static void send_to_everyone(char const *msg, client_t *clients, client_t *cli)
{
    for (int i = 0; i < SOMAXCONN; i++) {
        if (valid_client(&clients[i], cli)) {
            send_client(&clients[i], "message %d, %s\n", 0, msg);
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
        return send_client(cli, "ko\n");
    send_client(cli, "ok\n");
    send_to_everyone(arg, clients, cli);
}
