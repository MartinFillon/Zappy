/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** clock
*/

#pragma once

#include <stdbool.h>
#include <sys/types.h>

#include "core/types/clock.h"

/**
 * @brief Create a new clock
 *
 * @param frequency the frequency of the clock
 * @return zclock_t* the created clock
 */
zclock_t *clock_new(double frequency);

/**
 * @brief returns the elapsed time since clock creation or reset
 *
 * @param ztime_t the elapsed time
 */
ztime_t get_elapsed_time(zclock_t *this);

/**
 * @brief makes the program wait for n ticks
 *
 * @param n the number of ticks to wait
 */
void wait_n_ticks(zclock_t *this, uint n);

/**
 * @brief checks if n ticks have passed
 *
 * @param n the number of ticks to check
 * @return true if n ticks have passed, false otherwise
 */
bool has_n_ticks_passed(zclock_t *this, uint n);

/**
 * @brief resets the clock
 */
void reset_clock(zclock_t *this);
