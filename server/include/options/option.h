/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** option
*/

#pragma once

#include <stdbool.h>

enum arg_type {
    INT,
    STRING,
    UINT,
    FLOAT,
    BOOL,
};

typedef struct {
    char *identifier;
    enum arg_type type;
} option_t;

typedef struct {
    option_t *option;

    union data {
        int number;
        unsigned int unsigned_number;
        char *string;
        double flt;
        bool boolean;
    } value;
} argument_t;
