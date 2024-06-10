/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** va_free
*/

#include <stdarg.h>
#include <stdlib.h>

void va_free(int nb, ...)
{
    va_list list;

    va_start(list, nb);
    for (int i = 0; i < nb; i++)
        free(va_arg(list, void *));
    va_end(list);
}
