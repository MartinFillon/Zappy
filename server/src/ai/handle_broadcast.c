/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_broadcast
*/

#include "utils.h"
#include "types/client.h"
#include "client.h"

// Send to everyone the message and set the distance broadcast sound.
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
}
