/*
** EPITECH PROJECT, 2024
** logger
** File description:
** internal
*/

#pragma once

#include "logger.h"

struct logger_s {
    enum log_level level;
    int fd;
    char *names[5];
};
