/*
** EPITECH PROJECT, 2024
** teams
** File description:
** main
*/

#include <assert.h>
#include <stdio.h>

#include "json/map.h"
#include "json/json_parser.h"

static int parse_object_inner(json_parser_t *p)
{
    switch (get(p)) {
        case '"':
            return parse_key(p);
        case ',':
            return next(p);
        case ':':
            return parse_value(p);
        default:
            return 0;
    }
}

static void init_object(json_parser_t *p)
{
    json_data_t *elem = malloc(sizeof(json_data_t));

    elem->t = OBJECT;
    elem->data.obj = map_create_json_data_t(100);
    append_value(p, elem);
    p->self = elem;
}

int parse_object(json_parser_t *p)
{
    json_data_t *parent = p->self;

    init_object(p);
    if (skip_whitespace(p) == -1)
        return -1;
    if (get(p) == '{')
        next(p);
    while (get(p) != '}') {
        if (skip_whitespace(p) == -1)
            return -1;
        if (parse_object_inner(p) == -1)
            return -1;
        if (skip_whitespace(p) == -1)
            return -1;
    }
    next(p);
    if (parent != NULL)
        p->self = parent;
    return get(p);
}

struct map_json_data_t *json_get_object(
    json_data_t const *this,
    str_t const *key
)
{
    assert(this->t == OBJECT);
    return map_get_json_data_t(this->data.obj, key)->data.obj;
}
