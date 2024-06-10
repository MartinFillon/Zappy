/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** clock
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "core/types/clock.h"
#include "logger.h"

static ztime_t get_current_time(void)
{
    struct timeval tp;

    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000000 + tp.tv_usec;
}

zclock_t *clock_new(double frequency)
{
    zclock_t *clock = calloc(1, sizeof(zclock_t));

    clock->start = get_current_time();
    clock->frequency = (1 / frequency) * 1000000;
    return clock;
}

ztime_t get_elapsed_time(zclock_t *this)
{
    return get_current_time() - this->start;
}

bool has_n_ticks_passed(zclock_t *this, uint n)
{
    return get_current_time() > this->start + (this->frequency * n);
}

void wait_n_ticks(zclock_t *this, uint n)
{
    int i = 0;

    logs(INFO, "Elapsed time %llu microsseconds\n", get_elapsed_time(this));
    while (!has_n_ticks_passed(this, n)) {
        logs(DEBUG, "tick: %lu\n", i);
        usleep(this->frequency);
        i++;
    }
}

void reset_clock(zclock_t *this)
{
    this->start = get_current_time();
}
