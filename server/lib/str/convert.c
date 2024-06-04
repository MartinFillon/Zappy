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

bool str_toint(long *dest, const str_t *s)
{
    char *err;

    *dest = strtol(s->data, &err, 10);
    if (err == NULL || err[0] != '\0')
        return true;
    return false;
}
