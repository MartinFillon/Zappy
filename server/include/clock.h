/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** clock
*/

#pragma once

#include <stdbool.h>
#include <sys/types.h>

#include "types/clock.h"

zclock_t *clock_new(double frequency);
ztime_t get_elapsed_time(zclock_t *this);
void wait_n_ticks(zclock_t *this, uint n);
