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

union data {
    int number;
    unsigned int unsigned_number;
    str_t *string;
    double flt;
    bool boolean;
    struct vector_str_t *string_list;
};

union default_data {
    int number;
    unsigned int unsigned_number;
    char *string;
    double flt;
    bool boolean;
};

typedef struct {
    char *identifier;
    enum arg_type type;
    bool has_default;
    union default_data default_value;
    bool required;
    char *description;
} option_t;

typedef struct {
    option_t *option;

    union data value;
} argument_t;
