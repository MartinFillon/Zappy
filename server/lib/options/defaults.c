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
    logs(WARNING, "Using default value for option %s\n", opt->identifier);
}

void search_opt(option_t *opts, struct args *arguments, bool *found)
{
    for (size_t j = 0; j < arguments->size; j++) {
        if (!strcmp(opts->identifier, arguments->data[j].option->identifier)) {
            *found = true;
        }
    }
}

void set_default(union data *v, union default_data *d, enum arg_type type)
{
    switch (type) {
        case INT:
            v->number = d->number;
            break;
        case STRING:
            v->string = str_snew(d->string);
            break;
        case BOOL:
            v->boolean = d->boolean;
            break;
        case FLOAT:
            v->flt = d->flt;
            break;
        case UINT:
            v->unsigned_number = d->unsigned_number;
            break;
        case STRING_LIST:
            break;
    }
}

void set_defaults(struct options *opts, struct args *arguments)
{
    bool found = false;
    argument_t new = {0};

    for (size_t i = 0; i < opts->size; i++) {
        search_opt(&opts->data[i], arguments, &found);
        if (!found && opts->data[i].has_default) {
            new.option = &opts->data[i];
            set_default(
                &new.value, &opts->data[i].default_value, opts->data[i].type
            );
            warn_using_default(&opts->data[i]);
            vec_pushback_args(arguments, new);
        }
        new = (argument_t){0};
        found = false;
    }
}
