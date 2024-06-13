/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** converter
*/

#pragma once

#include <stddef.h>

#include "options/option.h"
#include "options/parser.h"

typedef bool (*fconverter_t)(argument_t *, parser_t *);

typedef struct {
    enum arg_type type;
    fconverter_t converter;
} converter_t;

bool convert_string(argument_t *, parser_t *);
bool convert_int(argument_t *, parser_t *);
bool convert_uint(argument_t *, parser_t *);
bool convert_float(argument_t *, parser_t *);
bool convert_bool(argument_t *, parser_t *);
bool convert_string_list(argument_t *, parser_t *);

static const converter_t CONVERTERS[] = {
    {
        .type = STRING,
        .converter = &convert_string,
    },
    {
        .type = INT,
        .converter = &convert_int,
    },
    {
        .type = UINT,
        .converter = &convert_uint,
    },
    {
        .type = FLOAT,
        .converter = &convert_float,
    },
    {
        .type = BOOL,
        .converter = &convert_bool,
    },
    {
        .type = STRING_LIST,
        .converter = &convert_string_list,
    },
    {
        .type = -1,
        .converter = NULL,
    },
};
