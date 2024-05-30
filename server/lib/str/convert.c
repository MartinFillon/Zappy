/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** convert
*/

#include <string.h>
#include "str.h"

char *str_cstr(str_t const *s)
{
    char *cstr = calloc(s->size + 1, sizeof(char));

    memcpy(cstr, s->data, s->size);
    return cstr;
}
