/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** free
*/

#include "str.h"

void str_free(str_t *s)
{
    free(s->data);
    free(s);
}
