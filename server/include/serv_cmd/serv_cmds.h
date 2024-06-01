/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** serv_cmds
*/

#pragma once

#include "server.h"
#include "zappy.h"

typedef struct serv_cmds_s {
    char const *name;
    void (*func)(zappy_t *z);
} serv_cmds_t;

void handle_display_map(zappy_t *z);
void handle_display_ais(zappy_t *z);
void handle_ressources_ais(zappy_t *z);

static const serv_cmds_t SERV_CMDS[] = {
    {"display", handle_display_map},
    {"ais", handle_display_ais},
    {"res-ais", handle_ressources_ais},
    {NULL, NULL}
};
