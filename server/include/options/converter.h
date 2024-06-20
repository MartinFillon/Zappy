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

/**
 * @brief Convert to string (`str_t`) the argument from the Parser Object
 *        @param parser to the current argument in @param arg
 *
 * @param arg Argument structure with the option and its value
 * @param parser Parser object for the command line arguments
 * @return False if it did, True if it failed.
 */
bool convert_string(argument_t *arg, parser_t *parser);

/**
 * @brief Convert to int the argument from the Parser Object @param parser
 *        to the current argument in @param arg
 *
 * @param arg Argument structure with the option and its value
 * @param parser Parser object for the command line arguments
 * @return False if it did, True if it failed.
 */
bool convert_int(argument_t *arg, parser_t *parser);

/**
 * @brief Convert to uint the argument from the Parser Object @param parser
 *        to the current argument in @param arg
 *
 * @param arg Argument structure with the option and its value
 * @param parser Parser object for the command line arguments
 * @return False if it did, True if it failed.
 */
bool convert_uint(argument_t *arg, parser_t *parser);

/**
 * @brief Convert to float the argument from the Parser Object @param parser
 *        to the current argument in @param arg
 *
 * @param arg Argument structure with the option and its value
 * @param parser Parser object for the command line arguments
 * @return False if it did, True if it failed.
 */
bool convert_float(argument_t *arg, parser_t *parser);

/**
 * @brief Convert to bool the argument from the Parser Object @param parser
 *        to the current argument in @param arg
 *
 * @param arg Argument structure with the option and its value
 * @param parser Parser object for the command line arguments
 * @return False if it did, True if it failed.
 */
bool convert_bool(argument_t *arg, parser_t *parser);

/**
 * @brief Convert to a string_list the argument from the Parser Object
 *        @param parser to the current argument in @param arg
 *
 * @param arg Argument structure with the option and its value
 * @param parser Parser object for the command line arguments
 * @return False if it did, True if it failed.
 */
bool convert_string_list(argument_t *arg, parser_t *parser);

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
