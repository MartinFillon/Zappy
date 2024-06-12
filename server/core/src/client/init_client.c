/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_client
*/

#include <string.h>

#include "core/client.h"
#include "core/types/client.h"

client_t init_client(int fd, char *address)
{
    client_t c = {0};

    c.fd = fd;
    c.io.req.buffer = NULL;
    c.io.req.size = 0;
    c.io.res.buffer = NULL;
    c.io.res.size = 0;
    c.ai = NULL;
    c.type = UNSET;
    c.commands = queue_create_queue_command_t(10);
    c.address = strdup(address);
    return c;
}
