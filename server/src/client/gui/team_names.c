/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** team_names
*/

#include <stdlib.h>
#include "client.h"
#include "types/client.h"

void team_names(char *args, client_t *c, game_t *g)
{
    if (c->type != GUI)
        return;
    if (args[0] != '\0')
        return send_client(c, "sbp\n");
    for (size_t i = 0; i < g->teams->len; i++)
        send_client(c, "tna %s\n", g->teams->data[i].name);
}
