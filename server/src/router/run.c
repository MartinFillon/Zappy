/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** run
*/

#include <stdio.h>
#include "router/router.h"

void run_router(struct router const *, str_t *line)
{
    struct vector_str_t *v = str_split(line, " \t");

    if (v->size == 0)
        return;
    vec_free_vector_str_t(v, &str_free);
}
