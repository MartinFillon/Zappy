/*
** EPITECH PROJECT, 2024
** lib
** File description:
** str
*/

#include <stdlib.h>
#include <string.h>

#include "str.h"

void str_resize(str_t *s)
{
    s->capacity *= 2;
    s->data = realloc(s->data, s->capacity);
}

void str_cadd(str_t *s, char const c)
{
    if (s->size + 1 >= s->capacity)
        str_resize(s);
    s->data[s->size] = c;
    s->size++;
}

void str_clear(str_t *s)
{
    s->data = memset(s->data, 0, s->capacity);
    s->size = 0;
}

int str_cmp(str_t const *this, str_t const *other)
{
    return strcmp(this->data, other->data);
}
