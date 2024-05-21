/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server
*/

#pragma once

#include <stdint.h>
#include <sys/select.h>
#include "args_info.h"

typedef struct server_s {
    int fd;
    fd_set read_fds;
    fd_set write_fds;
} server_t;

int server_init(uint32_t port);
int loop_server(args_infos_t *args);
