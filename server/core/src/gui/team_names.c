/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** team_names
*/

#include <stdlib.h>
#include "core/client.h"
#include "core/router/route.h"
#include "core/types/client.h"

void team_names(client_t *c, command_state_t *s)
{
    for (size_t i = 0; i < s->game->teams->size; i++)
        prepare_response_cat(&c->io, "tna %s\n", s->game->teams->data[i].name);
}
