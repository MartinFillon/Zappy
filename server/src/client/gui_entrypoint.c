/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** client_entrypoint
*/

#include <stdio.h>
#include "types/client.h"

int gui_entrypoint(char const *line, client_t *c, game_t *game)
{
    (void)game;
    dprintf(c->fd, "Gui received: %s\n", line);
    return 0;
}
