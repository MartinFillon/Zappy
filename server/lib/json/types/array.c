/*
** EPITECH PROJECT, 2024
** teams
** File description:
** main
*/

#include "vector.h"
#include "json/json_parser.h"

static void json_init_array(json_parser_t *p)
{
    json_data_t *elem = malloc(sizeof(json_data_t));

    elem->t = ARRAY;
    elem->data.arr = vec_create_vec_json_t(50);
    append_value(p, elem);
    p->self = elem;
    str_clear(p->current_key);
}

int parse_array(json_parser_t *p)
{
    json_data_t *parent = p->self;

    json_init_array(p);
    if (get(p) == '[')
        next(p);
    while (get(p) != ']') {
        if (skip_whitespace(p) == -1)
            return -1;
        if (parse_value(p) == -1)
            return -1;
        if (skip_whitespace(p) == -1)
            return -1;
        if (get(p) == ',')
            next(p);
    }
    next(p);
    if (parent != NULL)
        p->self = parent;
    return get(p);
}
