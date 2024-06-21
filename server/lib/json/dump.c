/*
** EPITECH PROJECT, 2024
** teams
** File description:
** main
*/

#include <stdio.h>
#include "json/json.h"

static void print_array(const int fd, struct vec_json_t *arr)
{
    dprintf(fd, "[");
    for (size_t i = 0; i < arr->size; i++) {
        if (i != 0)
            dprintf(fd, ",");
        print_data(fd, arr->data[i]);
    }
    dprintf(fd, "]\n");
}

void print_data(const int fd, json_data_t const *data)
{
    switch (data->t) {
        case OBJECT:
            print_json(fd, data);
            break;
        case STRING:
            dprintf(fd, "\"%s\"\n", data->data.str->data);
            break;
        case NUMBER:
            dprintf(fd, "%.2f\n", data->data.num);
            break;
        case BOOLEAN:
            dprintf(fd, "%s\n", data->data.boolean ? "true" : "false");
            break;
        case ARRAY:
            print_array(fd, data->data.arr);
            break;
        default:
            return;
    }
}

void print_json(const int fd, json_data_t const *json)
{
    struct map_json_data_t *obj = NULL;

    if (json->t != OBJECT)
        return;
    obj = json->data.obj;
    dprintf(fd, "{");
    for (size_t i = 0; i < obj->size; i++) {
        if (i != 0)
            dprintf(fd, ",");
        dprintf(fd, "\"%s\":", obj->data[i].key->data);
        print_data(fd, obj->data[i].data);
    }
    dprintf(fd, "}\n");
}
