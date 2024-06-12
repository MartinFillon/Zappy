/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tick
*/

#include <stddef.h>
#include <sys/time.h>

#include "core/types/clock.h"

ztime_t get_current_time(void)
{
    struct timeval tp;

    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000000 + tp.tv_usec;
}

ztime_t current_tick(zclock_t *const this)
{
    return (get_current_time() - this->start) / this->frequency;
}
