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
    char const *desc;
    size_t nb_args;
} serv_cmds_t;

#define DECLARE_COMMAND(name) void name(zappy_t *z, struct vector_str_t *args)

DECLARE_COMMAND(handle_display_map);
DECLARE_COMMAND(handle_display_ais);
DECLARE_COMMAND(handle_ressources_ais);
DECLARE_COMMAND(handle_display_eggs);
DECLARE_COMMAND(handle_help);
DECLARE_COMMAND(handle_kill_player);
DECLARE_COMMAND(godmode);
DECLARE_COMMAND(give);
DECLARE_COMMAND(teleport);

static const serv_cmds_t SERV_CMDS[] = {
    {
        "/display",
        handle_display_map,
        "Display the map with all the ai's positions\n",
        0,
    },
    {
        "/ais",
        handle_display_ais,
        "Display general information about the ais\n",
        0,
    },
    {
        "/ais-res",
        handle_ressources_ais,
        "Display the current ressources of all the ais\n",
        0,
    },
    {
        "/eggs",
        handle_display_eggs,
        "Display informations about the eggs currently on the map\n",
        0,
    },
    {
        "/kill",
        handle_kill_player,
        "<id>  Kill a player with a specific id\n",
        1,
    },
    {
        "/godmode",
        godmode,
        "<id> Switch the godmode state of a player\n",
        1,
    },
    {
        "/give",
        give,
        "<id> <object> <n> Give n object to a player (object is case "
        "insensitive)\n",
        3,
    },
    {
        "/tp",
        teleport,
        "<id> <id> Teleport the first player on the second one\n",
        2,
    },
    {
        "/help",
        handle_help,
        NULL,
        0,
    },
    {NULL, NULL, NULL, 0}
};
