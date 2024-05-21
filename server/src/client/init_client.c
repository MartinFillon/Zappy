/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_client
*/

#include "client.h"

void init_client(client_t *c)
{
    c->fd = 0;
    c->ffd = NULL;
    c->process_queue = NULL;
    c->ai = NULL;
    c->type = UNSET;
    c->entrypoint = &unset_entrypoint;
}
