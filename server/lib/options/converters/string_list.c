/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** int
*/

#include "logger.h"
#include "options/option.h"
#include "options/parser.h"
#include "str.h"

bool convert_string_list(argument_t *arg, parser_t *p)
{
    arg->value.string_list = vec_create_vector_str_t(p->args_size - p->idx);
    if (!arg->value.string_list)
        return true;
    while (p->idx < p->args_size && p->args[p->idx][0] != '-') {
        logs(
            DEBUG,
            "Adding %s to string list, idx: %d, max: %d\n",
            p->args[p->idx],
            p->idx,
            p->args_size
        );
        vec_pushback_vector_str_t(
            arg->value.string_list, str_snew(p->args[p->idx++])
        );
    }
    p->idx--;
    return false;
}
