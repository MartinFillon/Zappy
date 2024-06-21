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
#include "str.h"

static void warn_default(char *fmt, ...)
{
    str_t *str = str_snew("Using default value for option '%s': ");
    va_list args;

    if (str == NULL)
        return logs(ERROR_LEVEL, "Allocation level for 'str_t'\n");
    str_scadd(str, fmt);
    str_cadd(str, '\0');
    va_start(args, fmt);
    valogs(WARNING, str->data, args);
    va_end(args);
    str_free(str);
}

void search_opt(option_t *opts, struct args *arguments, bool *found)
{
    for (size_t j = 0; j < arguments->size; j++) {
        if (!strcmp(opts->identifier, arguments->data[j].option->identifier)) {
            *found = true;
        }
    }
}

void set_default(union data *v, union default_data *d, option_t *opt)
{
    switch (opt->type) {
        case INT:
            v->number = d->number;
            return warn_default("%d\n", opt->identifier, v->number);
        case STRING:
            v->string = str_snew(d->string);
            return warn_default("%s\n", opt->identifier, d->string);
        case BOOL:
            v->boolean = d->boolean;
            return warn_default("%s\n", opt->identifier,
                v->boolean ? "true" : "false");
        case FLOAT:
            v->flt = d->flt;
            return warn_default("%lf\n", opt->identifier, v->flt);
        case UINT:
            v->unsigned_number = d->unsigned_number;
            return warn_default("%lu\n", opt->identifier, v->unsigned_number);
        case STRING_LIST:
            return warn_default("");
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
                &new.value, &opts->data[i].default_value, &opts->data[i]
            );
            vec_pushback_args(arguments, new);
        }
        new = (argument_t){0};
        found = false;
    }
}
