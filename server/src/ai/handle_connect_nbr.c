/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_connect_nbr
*/

#include "types/client.h"
#include "client.h"
#include "utils.h"

void handle_connect_nbr(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
)
{
    (void) game;
    (void) clients;
    if (!is_empty(arg))
        return prepare_response(&cli->io, "ko\n");
    prepare_response(&cli->io, "%d\n", cli->ai->team->eggs->size);
}
