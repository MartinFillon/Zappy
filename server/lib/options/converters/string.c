/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** string
*/

#include <string.h>

#include "options/option.h"
#include "options/parser.h"

bool convert_uint(argument_t *arg, parser_t *const p)
{
    arg->value.string = strdup(p->args[p->idx]);
    return false;
}
