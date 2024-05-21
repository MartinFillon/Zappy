/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** logger_error
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief Function that will log any error message.
void logger_error(char const *fmt, ...)
{
    char *str = calloc(strlen("[Error]: ") + strlen(fmt) + 1, sizeof(char));

    if (!str)
        return;
    strcat(str, "[Error]: ");
    strcat(str, fmt);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, str, args);
    va_end(args);
}
