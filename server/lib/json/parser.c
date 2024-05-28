/*
** EPITECH PROJECT, 2024
** teams
** File description:
** main
*/

#include <ctype.h>
#include <stdio.h>
#include "str.h"

#include "json_parser.h"

int parse_value(json_parser_t *p)
{
    int chr = get(p);

    if (get(p) == ':')
        next(p);
    if (skip_whitespace(p) == -1)
        return -1;
    chr = get(p);
    if (chr == '"')
        return parse_string(p);
    if (chr == '{')
        return parse_object(p);
    if (chr == '[')
        return parse_array(p);
    if (chr == 't' || chr == 'f')
        return parse_boolean(p);
    if (chr == '-' || isdigit(chr))
        return parse_number(p);
    return -1;
}

json_data_t *json_parse(str_t *str)
{
    json_parser_t p = {NULL, str_snew(" "), 0, str};

    parse_value(&p);
    return p.self;
}
