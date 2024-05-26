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

void handle_rotate_right(client_t *cli, game_t *game)
{
    (void) game;
    cli->ai->dir = (cli->ai->dir + 1) % NB_DIR;
}

void handle_rotate_left(client_t *cli, game_t *game)
{
    (void) game;
    cli->ai->dir = modulo((cli->ai->dir - 1), NB_DIR);
}
