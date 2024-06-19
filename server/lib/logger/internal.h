/*
** EPITECH PROJECT, 2024
** logger
** File description:
** internal
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include "logger.h"

struct logger_s {
    enum log_level level;
    int fd;
    char *names[5];
    char *colors[5];
    bool tty;
};

struct level_parser_s {
    char *str;
    enum log_level level;
};

static const struct level_parser_s LEVELS[] = {
    {"ERROR", ERROR_LEVEL},
    {"WARNING", WARNING},
    {"INFO", INFO},
    {"DEBUG", DEBUG},
    {"DISABLE", DISABLE},
    {NULL, DISABLE}
};
