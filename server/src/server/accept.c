/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** accept
*/

#include <arpa/inet.h>
#include <sys/socket.h>

#include "client.h"
#include "define.h"
#include "server.h"
#include "utils.h"

int accept_new_client(server_t *s)
{
    struct sockaddr_in addr = {0};
    socklen_t addr_size = sizeof(addr);
    int fd = accept(s->fd, (struct sockaddr *)&addr, &addr_size);

    if (fd == -1) {
        logger_error("accept");
        return ERROR;
    }

    for (int i = 0; i < SOMAXCONN; i++) {
        if (s->clients[i].fd == -1) {
            init_client(&s->clients[i], fd);
            send_client(&s->clients[i], "WELCOME\n");
            return SUCCESS;
        }
    }
    return ERROR;
}
