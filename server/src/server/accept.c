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
#include "define.h"
#include "server.h"
#include "utils.h"

static int fill_client(server_t *s, int fd, struct sockaddr_in *addr)
{
    for (int i = 0; i < SOMAXCONN; i++) {
        if (s->clients[i].fd == 0) {
            init_client(&s->clients[i], fd);
            send_client(&s->clients[i], "WELCOME\n");
            logger_info(
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

int accept_new_client(server_t *s)
{
    struct sockaddr_in addr = {0};
    socklen_t addr_size = sizeof(addr);
    int fd = accept(s->fd, (struct sockaddr *)&addr, &addr_size);

    if (fd == -1) {
        logger_error("Accept failed\n");
        return ERROR;
    }
    return fill_client(s, fd, &addr);
}
