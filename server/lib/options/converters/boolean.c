/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** boolean
*/

#include "options/option.h"
#include "options/parser.h"

bool convert_bool(argument_t *arg, parser_t *p)
{
    arg->value.boolean = true;
    p->idx -= 1;
    return true;
}
