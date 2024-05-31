/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** team_names
*/

#include <stdlib.h>
#include "client.h"
#include "types/client.h"

void team_names(
    char *args,
    client_t *c,
    game_t *g,
    client_t *clients
)
{
    (void) clients;
    if (c->type != GUI)
        return;
    if (args[0] != '\0')
        return prepare_response(&c->io, "sbp\n");
    for (size_t i = 0; i < g->teams->size; i++)
        prepare_response(&c->io, "tna %s\n", g->teams->data[i].name);
}
