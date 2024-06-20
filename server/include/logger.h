/*
** EPITECH PROJECT, 2024
** logger
** File description:
** logger
*/

#pragma once

#include <stdarg.h>

enum log_level {
    DISABLE,
    ERROR_LEVEL,
    WARNING,
    INFO,
    DEBUG,
};

void logs(enum log_level level, char *fmt, ...);
int set_log_level(enum log_level level);
int set_log_level_from_str(char const *str);
void set_log_fd(int fd);
void valogs(enum log_level level, char *fmt, va_list l);
