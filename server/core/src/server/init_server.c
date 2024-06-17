/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_server
*/

#include <arpa/inet.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "logger.h"
#include "macros.h"

static int bind_server(int sock_fd, struct sockaddr_in *my_addr)
{
    if (bind(sock_fd, (struct sockaddr *)my_addr, sizeof(*my_addr)) == -1) {
        logs(ERROR_LEVEL, "Bind failed %s\n", strerror(errno));
        return ERROR;
    }
    return SUCCESS;
}

static int listen_to_port(int sock_fd, uint32_t port)
{
    if (listen(sock_fd, port) == -1) {
        logs(ERROR_LEVEL, "Listen failed %s\n", strerror(errno));
        return ERROR;
    }
    return SUCCESS;
}

static void set_addr(uint32_t port, struct sockaddr_in *my_addr)
{
    my_addr->sin_family = AF_INET;
    my_addr->sin_addr.s_addr = INADDR_ANY;
    my_addr->sin_port = htons(port);
}

static int socket_init(void)
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    int enable = 1;

    if (sock_fd == -1) {
        logs(ERROR_LEVEL, "Socket creation failed %s\n", strerror(errno));
        return ERROR;
    }
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &enable,
        sizeof(int)) < 0) {
        logs(ERROR_LEVEL, "setsockopt(SO_REUSEADDR) failed %s\n",
            strerror(errno));
        return ERROR;
    }
    return sock_fd;
}

int server_init(uint32_t port)
{
    struct sockaddr_in my_addr;
    int sock_fd = socket_init();

    set_addr(port, &my_addr);
    if (sock_fd == -1)
        return ERROR;
    if (bind_server(sock_fd, &my_addr) == ERROR)
        return ERROR;
    if (listen_to_port(sock_fd, port) == ERROR)
        return ERROR;
    return sock_fd;
}
