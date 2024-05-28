/*
** EPITECH PROJECT, 2024
** teams
** File description:
** main
*/

#include <ctype.h>

#include "json/json_parser.h"

int parse_number(json_parser_t *p)
{
    json_data_t *elem = calloc(1, sizeof(json_data_t));
    int found_dot = 0;
    char c = 0;

    elem->data.num = atof(p->data->data + p->index);
    if (get(p) == '-')
        c = next(p);
    c = get(p);
    while ((isdigit(c) || c == '.') && c != -1) {
        found_dot += (c == '.');
        c = next(p);
    }
    if (found_dot > 1 || c == -1)
        return -1;
    elem->t = NUMBER;
    return append_value(p, elem);
}
