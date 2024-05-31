/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_rotate
*/

#include <stdbool.h>

#include "client.h"
#include "router/route.h"
#include "types/ai.h"
#include "types/client.h"
#include "utils.h"

void handle_rotate_right(
    char const *arg,
    client_t *cli,
    game_t *game,
    client_t *clients
)
{
    if (!is_empty(arg))
        return prepare_response(&cli->io, "ko\n");
    (void)clients;
    (void)game;
    cli->ai->dir = (cli->ai->dir + 1) % NB_DIR;
    prepare_response(&cli->io, "ok\n");
}

void handle_rotate_left(client_t *cli, command_state_t *s)
{
    (void)s;
    cli->ai->dir = modulo((cli->ai->dir - 1), NB_DIR);
    prepare_response(&cli->io, "ok\n");
}
