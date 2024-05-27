/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** serv_cmds
*/

#pragma once

#include "server.h"

typedef struct serv_cmds_s {
    char const *name;
    void (*func)(server_t *serv);
} serv_cmds_t;

void handle_display_map(server_t *serv);

static const serv_cmds_t SERV_CMDS[] = {
    {"display", handle_display_map},
    {NULL, NULL}
};
