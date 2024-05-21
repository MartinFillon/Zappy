/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** logger_error
*/

#include <stdio.h>

/// @brief Function that will log any error message.
void logger_error(char const *mess, ...)
{
    dprintf(2, "Error: %s\n", mess);
}
