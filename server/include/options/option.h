/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** option
*/

#pragma once

#include <stdbool.h>
#include "str.h"

enum arg_type {
    INT,
    STRING,
    UINT,
    FLOAT,
    BOOL,
    STRING_LIST,
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
        str_t *string;
        double flt;
        bool boolean;
        struct vector_str_t *string_list;
    } value;
} argument_t;
