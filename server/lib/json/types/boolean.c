/*
** EPITECH PROJECT, 2024
** teams
** File description:
** main
*/

#include <assert.h>
#include "json/json.h"
#include "str.h"
#include "json/json_parser.h"

int parse_boolean(json_parser_t *p)
{
    json_data_t *elem = malloc(sizeof(json_data_t));

    elem->t = BOOLEAN;
    if (strncmp(p->data->data + p->index, "true", 4) == 0) {
        elem->data.boolean = true;
        p->index += 4;
    } else if (strncmp(p->data->data + p->index, "false", 5) == 0) {
        elem->data.boolean = false;
        p->index += 5;
    } else
        return -1;
    if (get(p) == -1)
        return -1;
    if (append_value(p, elem) != 0)
        return -1;
    return 0;
}

bool json_get_bool(json_data_t const *this, str_t const *key)
{
    assert(this->t == OBJECT);
    return map_get_json_data_t(this->data.obj, key)->data.boolean;
}
