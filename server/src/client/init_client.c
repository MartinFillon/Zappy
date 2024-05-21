/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_client
*/

#include "client.h"

void init_client(client_t *c, int fd)
{
    c->fd = fd;
    c->process_queue = NULL;
    c->ai = NULL;
    c->type = UNSET;
    c->entrypoint = &unset_entrypoint;
}
