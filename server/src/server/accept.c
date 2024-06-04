/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** accept
*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "client.h"
#include "logger.h"
#include "macros.h"
#include "server.h"
#include "types/client.h"

static int fill_client(client_t *clients, int fd, struct sockaddr_in *addr)
{
    for (int i = 0; i < SOMAXCONN; i++) {
        if (clients[i].fd == 0) {
            init_client(&clients[i], fd);
            prepare_response_cat(&clients[i].io, "WELCOME\n");
            logs(
                INFO,
                "New client %s:%d with fd %d\n",
                inet_ntoa(addr->sin_addr),
                ntohs(addr->sin_port),
                fd
            );
            return SUCCESS;
        }
    }
    return ERROR;
}

int accept_new_client(server_t *s, client_t *clients)
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
