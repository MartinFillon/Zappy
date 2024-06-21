/*
** EPITECH PROJECT, 2024
** teams
** File description:
** main
*/

#include <assert.h>

#include "json/json_parser.h"

static void add_escaped_char(json_parser_t *p, str_t *value)
{
    switch (get(p)) {
        case -1:
            return;
        case 'n':
            str_cadd(value, '\n');
            break;
        case 't':
            str_cadd(value, '\t');
            break;
        case 'r':
            str_cadd(value, '\r');
            break;
        default:
            str_cadd(value, get(p));
    }
}

int parse_string(json_parser_t *p)
{
    json_data_t *elem = malloc(sizeof(json_data_t));

    elem->data.str = str_new(10);
    elem->t = STRING;
    if (get(p) == '"')
        next(p);
    while (get(p) != '"' && get(p) != -1) {
        if (get(p) == '\\') {
            next(p);
            add_escaped_char(p, elem->data.str);
        } else
            str_cadd(elem->data.str, get(p));
        next(p);
    }
    next(p);
    append_value(p, elem);
    return get(p);
}

str_t *json_get_string(json_data_t const *this, str_t const *key)
{
    assert(this->t == OBJECT);
    return map_get_json_data_t(this->data.obj, key)->data.str;
}
