/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ai
*/

#pragma once

#include <stdlib.h>
#include "core/types/clock.h"
#include "core/types/position.h"
#include "core/types/team.h"

enum direction {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    NB_DIR,
};

typedef struct incant_state_s {
    int id_incant;
    bool is_incant;
    bool last_verif;
} incant_state_t;

typedef struct {
    team_t *team;

    pos_t pos;
    size_t level;
    incant_state_t incant;

    enum direction dir;

    size_t *inventory;
    long cycles_to_wait; // if current time < this time dont do anything
    zclock_t *clock;
    zclock_t *food_clock;

    bool alive;
    int id;

    bool godmode;
} ai_t;
