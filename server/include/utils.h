/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** utils
*/

#pragma once

#include <stdbool.h>

void logger_debug(char const *fmt, ...);
void logger_info(char const *fmt, ...);
void logger_warn(char const *fmt, ...);
void logger_error(char const *fmt, ...);
void my_free_box(char **arr);
void va_free(int nb, ...);
[[nodiscard]] bool parse_number(char *restrict args, long *restrict n);
