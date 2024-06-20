/*
** EPITECH PROJECT, 2024
** logger
** File description:
** logger
*/

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>
#include <bits/types/struct_timeval.h>

#include "internal.h"
#include "logger.h"

#ifndef TEST
static
#endif
struct logger_s *get_mut_logger(void)
{
    static struct logger_s logger = {
        ERROR_LEVEL,
        2,
        {"", "ERROR", "WARNING", "INFO", "DEBUG"},
        {"", "\033[31m", "\033[33m", "\033[32m", "\033[34m"},
        false
    };

    logger.tty = isatty(logger.fd);
    return &logger;
}

static struct logger_s const *get_logger(void)
{
    return get_mut_logger();
}

// yyyy-MM-dd'T'HH:mm:ss.SSS'Z'
//  ISO8601
static void print_time(time_t *t, struct logger_s const *logger)
{
    char buf[sizeof "2011-10-08T07:07:09Z"];

    strftime(buf, sizeof(buf), "%FT%TZ", gmtime(t));
    dprintf(logger->fd, "[%s", buf);
}

void valogs(enum log_level level, char *fmt, va_list l)
{
    struct logger_s const *logger = get_logger();
    time_t t;

    time(&t);
    if (logger->level == DISABLE)
        return;
    if (logger->level >= level && level >= ERROR_LEVEL && level <= DEBUG) {
        print_time(&t, logger);
        dprintf(
            logger->fd,
            " %s%s%s]: ",
            logger->tty ? logger->colors[level] : "",
            logger->names[level],
            logger->tty ? "\033[0m" : ""
        );
        vdprintf(logger->fd, fmt, l);
    }
}

void logs(enum log_level level, char *fmt, ...)
{
    va_list l;

    va_start(l, fmt);
    valogs(level, fmt, l);
    va_end(l);
}

int set_log_level(enum log_level level)
{
    struct logger_s *l = get_mut_logger();

    l->level = level;
    return level;
}

int set_log_level_from_str(char const *str)
{
    if (!str)
        return set_log_level(ERROR_LEVEL);
    for (__auto_type i = 0; LEVELS[i].str; i++)
        if (strcasecmp(str, LEVELS[i].str) == 0)
            return set_log_level(LEVELS[i].level);
    set_log_level(ERROR_LEVEL);
    logs(ERROR_LEVEL, "Unknown level setting back to default: ERROR\n");
    return ERROR_LEVEL;
}
