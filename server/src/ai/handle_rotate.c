/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_rotate
*/

#include <stdbool.h>

#include "types/ai.h"
#include "types/client.h"
#include "utils.h"
#include "client.h"

void handle_rotate_right(char const *arg, client_t *cli, game_t *game)
{
    if (!is_empty(arg))
        return send_client(cli, "ko\n");
    (void) game;
    cli->ai->dir = (cli->ai->dir + 1) % NB_DIR;
    send_client(cli, "ok\n");
}

void handle_rotate_left(char const *arg, client_t *cli, game_t *game)
{
    if (!is_empty(arg))
        return send_client(cli, "ko\n");
    (void) game;
    cli->ai->dir = modulo((cli->ai->dir - 1), NB_DIR);
    send_client(cli, "ok\n");
}
