/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** duration
*/

#include "time/duration.h"
#include <stdbool.h>

void new_duration_from_seconds(zduration_t *this, double seconds)
{
    *this = seconds * MICROSECONDS_CONVERTER;
}
