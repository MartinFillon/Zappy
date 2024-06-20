/*
** EPITECH PROJECT, 2024
** teams
** File description:
** main
*/

#include <assert.h>
#include <ctype.h>

#include "json/json_parser.h"

int parse_json_number(json_parser_t *p)
{
    json_data_t *elem = calloc(1, sizeof(json_data_t));
    int found_dot = 0;
    char c = 0;

    elem->data.num = atof(p->data->data + p->index);
    if (get(p) == '-')
        c = next(p);
    c = get(p);
    while ((isdigit(c) || c == '.')) {
        found_dot += (c == '.');
        c = next(p);
    }
    if (found_dot > 1 || c == -1)
        return -1;
    elem->t = NUMBER;
    return append_value(p, elem);
}

double json_get_number(json_data_t const *this, str_t const *key)
{
    assert(this->t == OBJECT);
    return map_get_json_data_t(this->data.obj, key)->data.num;
}

double json_get_number_raw(json_data_t const *this, char const *rkey)
{
    str_t *key = str_snew(rkey);
    double res = 0;

    assert(this->t == OBJECT);
    res = map_get_json_data_t(this->data.obj, key)->data.num;
    str_free(key);
    return res;
}
