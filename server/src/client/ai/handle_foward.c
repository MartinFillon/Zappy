/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_foward
*/

#include <stdio.h>

#include "ai/ai_cmds.h"

int handle_forward(client_t *cli, game_t *game)
{
    (void) game;
    dprintf(cli->fd, "ok\n");
    return 0;
}
