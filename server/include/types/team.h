/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** team
*/

#pragma once

#include <stddef.h>
#include "types/position.h"

typedef pos_t egg_t;

typedef struct {
    egg_t *data;
    size_t len;
    size_t size;
} eggs_t;

typedef struct {
    char *name;
    eggs_t eggs;
} team_t;

team_t create_team(char const *name);
