/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** broadcast
*/

#include <stdarg.h>
#include <stdio.h>
#include "vector.h"

void broadcast(struct vector_int *v, char *fmt, ...)
{
    va_list l;

    va_start(l, fmt);
    for (__auto_type i = 0ul; i < v->size; i++)
        vdprintf(v->data[i], fmt, l);
    va_end(l);
}
