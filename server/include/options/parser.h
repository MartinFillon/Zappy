/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** parser
*/

#pragma once

#include "options/option.h"
#define TYPE option_t
#define NAME options
#include "vector.h"

#include "options/option.h"
#define TYPE argument_t
#define NAME args
#include "vector.h"

typedef struct {
    struct options *options;
    char **args;
    size_t args_size;
    size_t idx;
} parser_t;

/**
 * @brief Parse the arguments according to the options defined in the third
 * argument and return a struct containing the arguments
 * @param args The arguments to parse
 * @param count The number of arguments
 * @param opts The options to parse the arguments with
 *
 * @return struct args* The parsed arguments
 */
struct args *parse(char **args, size_t count, struct options *opts);
