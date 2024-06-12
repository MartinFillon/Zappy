/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** accept
*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "core/client.h"
#include "core/server.h"
#include "core/types/client.h"
#include "logger.h"
#include "macros.h"

static int fill_client(
    struct client_list *clients,
    int fd,
    struct sockaddr_in *addr
)
{
    client_t c = init_client(fd, inet_ntoa(addr->sin_addr));

    prepare_response_cat(&c.io, "WELCOME\n");
    logs(
        INFO,
        "New client %s:%d with fd %d\n",
        inet_ntoa(addr->sin_addr),
        ntohs(addr->sin_port),
        fd
    );
    vec_pushback_client_list(clients, c);
    return SUCCESS;
}

int accept_new_client(server_t *s, struct client_list *clients)
{
    struct sockaddr_in addr = {0};
    socklen_t addr_size = sizeof(addr);
    int fd = accept(s->fd, (struct sockaddr *)&addr, &addr_size);

    if (fd == -1) {
        logs(ERROR, "Accept failed\n");
        return ERROR;
    }
    return fill_client(clients, fd, &addr);
}
