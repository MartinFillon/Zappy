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

typedef bool (*fconverter_t)(argument_t *, parser_t *const);

typedef struct {
    enum arg_type type;
    fconverter_t converter;
} converter_t;

bool convert_string(argument_t *, parser_t *const);
bool convert_int(argument_t *, parser_t *const);
bool convert_uint(argument_t *, parser_t *const);

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
        .type = -1,
        .converter = NULL,
    },
};
