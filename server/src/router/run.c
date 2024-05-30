/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** run
*/

#include <stdio.h>
#include "router/router.h"
#include "types/client.h"

route_t *get_route(struct router const *r, str_t *name)
{
    for (__auto_type i = 0ul; i < r->size; i++) {
        if (str_cmp(r->data[i]->name, name) == 0)
            return r->data[i];
    }
    return NULL;
}

void run_router(enum client_type_e cli, struct router const *r, str_t *line)
{
    struct vector_str_t *v = str_split(line, " \t");

    if (v->size == 0)
        return;
    route_t *route = get_route(r, v->data[0]);
    vec_free_vector_str_t(v, &str_free);
}
