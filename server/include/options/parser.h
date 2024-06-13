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

/**
 * @brief Get the argument value from the argument struct
 * @param args The argument list
 * @param name The name of the argument
 *
 * @return union data The value of the argument
 */
union data get_arg(struct args *args, char *name);

/**
 * @brief Free the argument struct
 * @param ag The argument struct to free
 */
void free_args(struct args *ag);

/**
 * @brief set the default values for the options
 * @param opts The options to set the default values for
 * @param arguments The arguments to set the values with
 */
void set_defaults(struct options *opts, struct args *arguments);

/**
 * @brief Check if the required options are present in the arguments
 * @param opts The options to check the required options for
 * @param arguments The arguments to check the required options with
 *
 * @return bool true if all the required options are present, false otherwise
 */
bool check_required(struct options *opts, struct args *arguments);
