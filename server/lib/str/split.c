/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** split
*/

#include "str.h"
#include "vector.h"

struct vector_str_t *split(char *s, char *delim)
{
    char *tmp = strtok(s, delim);
    struct vector_str_t *v = vec_create_vector_str_t(10);

    while (tmp) {
        vec_pushback_vector_str_t(v, str_snew(tmp));
        tmp = strtok(NULL, delim);
    }
    return v;
}
