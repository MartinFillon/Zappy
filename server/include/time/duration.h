/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** duration
*/

#pragma once

#define MICROSECONDS_CONVERTER 1000000

/*
** @DESCRIPTION
**   Duration type
** @NOTE
**   This type is used to represent a duration in microseconds
*/
typedef long long unsigned zduration_t;

/*
 * @brief Create a new duration from seconds
 *
 * @param this the duration to create
 * @param seconds the duration in seconds
 */
void new_duration_from_seconds(zduration_t *this, double seconds);
