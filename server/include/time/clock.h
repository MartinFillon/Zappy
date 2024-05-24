/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** clock
*/

#pragma once

#include <stdbool.h>
#include "time/duration.h"

typedef long long unsigned ztime_t;

typedef struct {
    ztime_t start;
    zduration_t duration;
} zclock_t;

bool has_time_passed(zclock_t const *this);
void clock_initialize(zclock_t *this);
void set_clock_duration(zclock_t *this, zduration_t *duration);
