/*
** EPITECH PROJECT, 2024
** logger
** File description:
** logger
*/

#include <stdarg.h>
#include <stdio.h>

#include "internal.h"
#include "logger.h"

static struct logger_s *get_mut_logger(void)
{
    static struct logger_s logger = {
        ERROR, 2, {"", "ERROR", "WARNING", "INFO", "DEBUG"}
    };

    return &logger;
}

static struct logger_s const *get_logger(void)
{
    return get_mut_logger();
}

void logs(enum log_level level, char *fmt, ...)
{
    struct logger_s const *logger = get_logger();
    va_list l;

    if (logger->level == DISABLE)
        return;
    if (logger->level >= level && level >= INFO && level <= DEBUG) {
        va_start(l, fmt);
        dprintf(logger->fd, "[%s]: ", logger->names[level]);
        vdprintf(logger->fd, fmt, l);
        va_end(l);
    }
}

void set_log_level(enum log_level level)
{
    struct logger_s *l = get_mut_logger();

    l->level = level;
}

void set_log_fd(int fd)
{
    struct logger_s *l = get_mut_logger();

    l->fd = fd;
}
