/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** defaults
*/

#include <stdlib.h>

#include "logger.h"
#include "options/option.h"
#include "options/parser.h"

static void warn_using_default(option_t *opt)
{
    logs(WARNING, "Using default value for option %s", opt->identifier);
}

void search_opt(option_t *opts, struct args *arguments, bool *found)
{
    for (size_t j = 0; j < arguments->size; j++) {
        if (!strcmp(opts->identifier, arguments->data[j].option->identifier)) {
            *found = true;
        }
    }
}

void set_defaults(struct options *opts, struct args *arguments)
{
    bool found = false;
    argument_t new = {0};

    for (size_t i = 0; i < opts->size; i++, found = false) {
        search_opt(&opts->data[i], arguments, &found);
        if (!found && opts->data[i].has_default) {
            new.option = &opts->data[i];
            if (opts->data[i].type == STRING)
                new.value.string = str_dup(opts->data[i].default_value.string);
            else
                new.value = opts->data[i].default_value;
            warn_using_default(&opts->data[i]);
            vec_pushback_args(arguments, new);
        }
        new = (argument_t){0};
    }
}
