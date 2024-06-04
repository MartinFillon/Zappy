/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** team
*/

#pragma once

#include <stddef.h>
#include "types/position.h"
#include "args_info.h"

typedef struct {
    size_t id;
    pos_t pos;
} egg_t;

#define TYPE egg_t *
#define NAME queue_egg_t
#include "queue.h"

typedef struct {
    char *name;
    struct queue_egg_t *eggs;
} team_t;

team_t create_team(args_infos_t *args, char const *name);
egg_t *create_egg(int width, int height);
void destroy_team(team_t *team);
