/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** new
*/

#include <string.h>
#include "str.h"

str_t *str_snew(char const *data)
{
    str_t *s = calloc(1, sizeof(str_t));

    s->data = strdup(data);
    s->capacity = strlen(data);
    s->size = strlen(data);
    return s;
}

str_t *str_new(size_t size)
{
    str_t *s = calloc(1, sizeof(str_t));

    s->data = calloc(size, sizeof(char));
    s->capacity = size;
    s->size = 0;
    return s;
}

str_t *str_dup(str_t const *str)
{
    str_t *s = calloc(1, sizeof(str_t));

    s->data = calloc(str->capacity, sizeof(char));
    s->capacity = str->capacity;
    s->size = str->size;
    memcpy(s->data, str->data, str->size);
    return s;
}
