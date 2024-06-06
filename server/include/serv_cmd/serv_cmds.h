/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** serv_cmds
*/

#pragma once

#include "zappy.h"

typedef struct serv_cmds_s {
    char const *name;
    void (*func)(zappy_t *z, struct vector_str_t *args);
} serv_cmds_t;

void handle_display_map(zappy_t *z, struct vector_str_t *args);
void handle_display_ais(zappy_t *z, struct vector_str_t *args);
void handle_ressources_ais(zappy_t *z, struct vector_str_t *args);
void handle_display_eggs(zappy_t *serv, struct vector_str_t *args);

static const serv_cmds_t SERV_CMDS[] = {
    {"/display", handle_display_map},
    {"/ais", handle_display_ais},
    {"/ais-res", handle_ressources_ais},
    {"/eggs", handle_display_eggs},
    {NULL, NULL}
};
