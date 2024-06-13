/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** string
*/

#include "options/option.h"
#include "options/parser.h"

bool convert_string(argument_t *arg, parser_t *p)
{
    arg->value.string = str_snew(p->args[p->idx]);
    return false;
}
