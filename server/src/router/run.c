/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** run
*/

#include <stdio.h>
#include "router/router.h"

void run_router(struct router const *, char *line)
{
    struct vector_str_t *v = split(line, " \t");

    for (__auto_type i = 0ul; i < v->size; i++)
        dprintf(2, "%s\n", v->data[i]->data);

    vec_free_vector_str_t(v, &str_free);
}
