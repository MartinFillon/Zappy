/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** int
*/

#include <stdlib.h>

#include "options/option.h"
#include "options/parser.h"

bool convert_uint(argument_t *arg, parser_t *p)
{
    char *eptr = NULL;

    arg->value.unsigned_number = strtoul(p->args[p->idx], &eptr, 10);
    if (eptr != NULL && eptr[0] != '\0') {
        return true;
    }
    return false;
}
