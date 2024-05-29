/*
** EPITECH PROJECT, 2024
** teams
** File description:
** main
*/

#include "json/json.h"
#include "str.h"

static bool find_key(
    json_data_t const *this,
    str_t const *key,
    types_t const type
)
{
    for (size_t i = 0; i < this->data.obj->size; i++)
        if (str_cmp(this->data.obj->data[i].key, key) == 0 &&
            this->data.obj->data[i].data->t == type)
            return true;
    return false;
}

bool validate_schema(json_data_t const *this, json_data_t const *schema)
{
    for (size_t i = 0; i < schema->data.obj->size; i++) {
        if (find_key(
                this,
                schema->data.obj->data[i].key,
                schema->data.obj->data[i].data->t
            ))
            return true;
    }
    return false;
}
