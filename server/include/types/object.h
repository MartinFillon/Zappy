/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** object
*/

#pragma once

#define NB_OBJ 7

enum object_e {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
};

struct obj_name_s {
    char const *name;
    enum object_e obj;
};

static const struct obj_name_s all_obj[] = {
    {"food", FOOD},
    {"linemate", LINEMATE},
    {"deraumere", DERAUMERE},
    {"sibur", SIBUR},
    {"mendiane", MENDIANE},
    {"phiras", PHIRAS},
    {"thystame", THYSTAME}
};
