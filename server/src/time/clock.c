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

#include "macros.h"
#include "types/clock.h"
#include "utils.h"

static ztime_t get_current_time(void)
{
    struct timeval tp;

    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

zclock_t *clock_new(double frequency)
{
    zclock_t *clock = calloc(1, sizeof(zclock_t));

    clock->start = get_current_time();
    clock->frequency = 1 / frequency;
    return clock;
}

ztime_t get_elapsed_time(zclock_t *this)
{
    return get_current_time() - this->start;
}

void wait_n_ticks(zclock_t *this, uint n)
{
    logger_info("Elapsed time %llu\n", get_elapsed_time(this));
    for (size_t i = 0; i < n; i++) {
        logger_debug("tick: %lu\n", i);
        // sleep(unsigned int seconds)
    }
}
