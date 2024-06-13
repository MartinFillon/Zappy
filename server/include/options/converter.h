/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** converter
*/

#pragma once

#include <stddef.h>

#include "options/option.h"

typedef struct {
    enum arg_type type;
    union data (*converter)(char const *);
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
