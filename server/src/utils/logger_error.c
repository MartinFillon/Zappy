/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** logger_error
*/

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

/// @brief Function that will log any error message.
void logger_error(char const *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    dprintf(STDERR_FILENO, "[ERROR]: ");
    vdprintf(STDERR_FILENO, fmt, args);
    va_end(args);
}

void logger_debug(char const *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    dprintf(STDERR_FILENO, "[DEBUG]: ");
    vdprintf(STDERR_FILENO, fmt, args);
    va_end(args);
}

void logger_info(char const *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    dprintf(STDERR_FILENO, "[INFO]: ");
    vdprintf(STDERR_FILENO, fmt, args);
    va_end(args);
}

void logger_warn(char const *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    dprintf(STDERR_FILENO, "[WARN]: ");
    vdprintf(STDERR_FILENO, fmt, args);
    va_end(args);
}
