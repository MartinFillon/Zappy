/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** converter
*/

#pragma once

#include <stddef.h>

#include "options/option.h"

typedef union data (*fconverter_t)(char const *);

typedef struct {
    enum arg_type type;
    fconverter_t converter;
} converter_t;

#define REGISTER_CONVERTER(name) union data convert_##name(char const *)

REGISTER_CONVERTER(string);

static const converter_t CONVERTERS[] = {
    {
        .type = STRING,
        .converter = &convert_string,
    },
    {
        .type = -1,
        .converter = NULL,
    },
};
