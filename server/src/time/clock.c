/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** clock
*/

#include <stdbool.h>
#include <stddef.h>
#include <sys/time.h>

#include "time/clock.h"
#include "time/duration.h"

static ztime_t get_current_time(void)
{
    struct timeval tp;

    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

void clock_initialize(zclock_t *this)
{
    this->start = get_current_time();
    this->duration = 0;
}

void set_clock_duration(zclock_t *this, zduration_t *duration)
{
    this->duration = *duration;
}

bool has_time_passed(zclock_t const *this)
{
    ztime_t curr = get_current_time();

    return (this->start + this->duration) > curr;
}
