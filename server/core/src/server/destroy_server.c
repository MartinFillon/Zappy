/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** destroy_server
*/

#include <sys/select.h>
#include <unistd.h>

#include "core/router/router.h"
#include "core/server.h"

void free_wifi(server_t *s)
{
    destroy_router(s->router);
    close(s->fd);
    FD_ZERO(&s->read_fds);
    FD_ZERO(&s->write_fds);
}
