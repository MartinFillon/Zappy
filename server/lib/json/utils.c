/*
** EPITECH PROJECT, 2024
** teams
** File description:
** main
*/

#include <stdio.h>
#include "json/json_parser.h"

int get(json_parser_t *p)
{
    if (p->index >= p->data->size)
        return -1;
    return p->data->data[p->index];
}

int next(json_parser_t *p)
{
    if (p->index >= p->data->size)
        return -1;
    p->index += 1;
    return p->data->data[p->index];
}

int skip_whitespace(json_parser_t *p)
{
    char c = get(p);

    while (c == ' ' || c == '\t' || c == '\n')
        c = next(p);
    return c;
}

int append_value(json_parser_t *p, json_data_t *elem)
{
    if (p->self == NULL && elem->t == OBJECT) {
        p->self = elem;
        return 0;
    }
    if (p->self->t == OBJECT) {
        dprintf(2, "pushing %s\n", p->current_key->data);
        map_push_json_data_t(p->self->data.obj, str_dup(p->current_key), elem);
        return 0;
    }
    if (p->self->t == ARRAY) {
        vec_pushback_vec_json_t(p->self->data.arr, elem);
        return 0;
    }
    return -1;
}

int parse_key(json_parser_t *p)
{
    next(p);
    str_clear(p->current_key);
    while (get(p) != '"' && get(p) != -1) {
        str_cadd(p->current_key, get(p));
        next(p);
    }
    next(p);
    return get(p);
}
