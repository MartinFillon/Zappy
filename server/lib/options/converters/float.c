/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** int
*/

#include <stdio.h>
#include "logger.h"
#include "options/option.h"
#include "options/parser.h"

bool convert_float(argument_t *arg, parser_t *p)
{
    char *eptr = NULL;

    arg->value.flt = strtod(p->args[p->idx], &eptr);
    if (eptr != NULL && eptr[0] != '\0') {
        logs(ERROR_LEVEL, "Invalid float value: %s\n", p->args[p->idx]);
        return true;
    }
    return false;
}
