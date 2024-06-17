/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** join
*/

#include <stdlib.h>

#include "str.h"

str_t *join_between_strs(
    struct vector_str_t *array,
    char const *sep,
    size_t start,
    size_t end
)
{
    str_t *new = str_dup(array->data[start]);

    for (size_t i = start + 1; i < end; i++) {
        str_scadd(new, sep);
        str_sadd(new, array->data[i]);
    }
    return new;
}

str_t *join_n_end_strs(struct vector_str_t *array, char const *sep, size_t end)
{
    return join_between_strs(array, sep, 0, end);
}

str_t *join_n_start_strs(
    struct vector_str_t *array,
    char const *sep,
    size_t start
)
{
    return join_between_strs(array, sep, start, array->size);
}

str_t *join_strs(struct vector_str_t *array, char const *sep)
{
    return join_between_strs(array, sep, 0, array->size);
}
