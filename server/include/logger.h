/*
** EPITECH PROJECT, 2024
** logger
** File description:
** logger
*/

#pragma once

enum log_level {
    DISABLE,
    ERROR_LEVEL,
    WARNING,
    INFO,
    DEBUG,
};

void logs(enum log_level level, char *fmt, ...);
void set_log_level(enum log_level level);
