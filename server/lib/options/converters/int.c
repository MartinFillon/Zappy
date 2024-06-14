/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** int
*/

#include "options/option.h"
#include "options/parser.h"

bool convert_int(argument_t *arg, parser_t *p)
{
    char *eptr = NULL;

    arg->value.number = strtol(p->args[p->idx], &eptr, 10);
    if (eptr != NULL && eptr[0] != '\0') {
        return true;
    }
    return false;
}
