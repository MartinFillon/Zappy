/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** parser
*/

#include <stdlib.h>

#include "logger.h"
#include "options/converter.h"
#include "options/option.h"
#include "options/parser.h"

static fconverter_t find_converter(enum arg_type type)
{
    for (size_t i = 0; CONVERTERS[i].converter != NULL; i++) {
        if (CONVERTERS[i].type == type)
            return CONVERTERS[i].converter;
    }
    return NULL;
}

static option_t *get_option(char *const arg, struct options *const opts)
{
    for (size_t i = 0; i < opts->size; i++) {
        if (!strcmp(opts->data[i].identifier, arg)) {
            logs(DEBUG, "Found option: %s\n", arg);
            return &opts->data[i];
        }
    }
    logs(ERROR_LEVEL, "Unknown option: %s\n", arg);
    return NULL;
}

static bool parse_argument(struct args *lst, char *const arg, option_t *opts)
{
    fconverter_t f = find_converter(opts->type);
    argument_t argument = {0};

    if (f == NULL) {
        logs(
            ERROR_LEVEL,
            "Couldn't find a converter for the argument %s\n",
            opts->type
        );
        return true;
    }
    argument.value = f(arg);
    argument.option = opts;
    vec_pushback_args(lst, argument);
    return false;
}

static bool parse_inner(parser_t *parser, struct args *lst)
{
    option_t *opt = NULL;

    opt = get_option(parser->args[parser->idx], parser->options);
    if (opt == NULL)
        return true;
    parser->idx += 1;
    if (parser->idx >= parser->args_size) {
        logs(DEBUG, "Missing value for argument: %s\n", opt->identifier);
        return true;
    }
    return parse_argument(lst, parser->args[parser->idx], opt);
}

void free_args(struct args *lst)
{
    for (size_t i = 0; i < lst->size; i++)
        if (lst->data[i].option->type == STRING)
            free(lst->data[i].value.string);
    vec_destroy_args(lst);
}

struct args *parse(char **args, size_t count, struct options *opts)
{
    struct args *lst = vec_create_args(count);
    parser_t parser = {opts, args, count, 1};
    bool error = false;

    for (; parser.idx < count; parser.idx++) {
        logs(DEBUG, "Parsing: %s\n", args[parser.idx]);
        error |= parse_inner(&parser, lst);
    }
    if (error) {
        free_args(lst);
        return NULL;
    }
    return lst;
}
