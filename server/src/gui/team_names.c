/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** team_names
*/

#include <stdlib.h>
#include "client.h"
#include "router/route.h"
#include "types/client.h"

void team_names(client_t *c, command_state_t *s)
{
    for (size_t i = 0; i < s->game->teams->size; i++)
        send_client(c, "tna %s\n", s->game->teams->data[i].name);
}
