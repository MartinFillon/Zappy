/*
** EPITECH PROJECT, 2024
** logger
** File description:
** logger
*/

#pragma once

void logger_error(char *fmt, ...);

enum log_level {
    DISABLE,
    ERROR,
    WARNING,
    INFO,
    DEBUG,
};

void logs(enum log_level level, char *fmt, ...);
void set_log_level(enum log_level level);
