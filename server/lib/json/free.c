/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** free
*/

#include "json/json.h"
#include "utils.h"

static void free_str(json_data_t *s)
{
    free(s->data.str->data);
    free(s->data.str);
    free(s);
}

static void free_not_allowed(json_data_t *s)
{
    free(s);
}

static void free_arr(json_data_t *s)
{
    for (__auto_type i = 0ul; i < s->data.arr->size; i++)
        json_free(s->data.arr->data[i]);
    free(s->data.arr->data);
    free(s->data.arr);
    free(s);
}

static void free_map(json_data_t *s)
{
    for (__auto_type i = 0ul; i < s->data.obj->size; i++) {
        free(s->data.obj->data[i].key->data);
        free(s->data.obj->data[i].key);
        json_free(s->data.obj->data[i].data);
    }
    free(s->data.obj->data);
    free(s->data.obj);
    free(s);
}

void json_free(json_data_t *json)
{
    void (*free_funcs[5])(json_data_t *) = {
        &free_not_allowed,
        &free_map,
        &free_arr,
        &free_not_allowed,
        &free_str,
    };

    if (json == NULL)
        return;
    free_funcs[json->t](json);
}
