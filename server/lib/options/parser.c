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

static union data (*find_converter(enum arg_type type))(char const *)
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
    union data (*f)(char const *) = find_converter(opts->type);
    union data v = {0};

    if (f == NULL) {
        logs(
            ERROR_LEVEL,
            "Couldn't find a converter for the argument %s\n",
            opts->type
        );
        return false;
    }
    v = f(arg);
    vec_pushback_args(
        lst,
        (argument_t){
            .option = opts,
            .value = v,
        }
    );
    return true;
}

static bool parse_inner(
    char **args,
    size_t *i,
    size_t max,
    struct options *opts,
    struct args *lst
)
{
    option_t *opt = NULL;

    opt = get_option(args[*i], opts);
    if (opt == NULL)
        return false;
    *i += 1;
    if (*i >= max) {
        logs(DEBUG, "Missing value for argument: %s\n", opt->identifier);
        return false;
    }
    parse_argument(lst, args[*i], opt);
    return true;
}

struct args *parse(char **args, size_t count, struct options *opts)
{
    struct args *lst = vec_create_args(count);

    for (size_t i = 1; i < count; i++) {
        logs(DEBUG, "Parsing: %s\n", args[i]);
        parse_inner(args, &i, count, opts, lst);
    }
    return NULL;
}
