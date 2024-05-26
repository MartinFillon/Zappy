/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** vector_ai
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "types/team.h"
#include "utils.h"

bool resize_vector_team(teams_t *v)
{
    v->size *= 2;
    v->data = realloc(v->data, v->size * sizeof(team_t));
    return false;
}

void push_back_vector_team(teams_t *v, const team_t *nw)
{
    if (v->len + 1 > v->size)
        resize_vector_team(v);
    memcpy(v->data + v->len, nw, sizeof(team_t));
    v->len += 1;
}

teams_t *init_teams(size_t team_count)
{
    teams_t *nw = calloc(1, sizeof(teams_t));

    nw->data = calloc(1, sizeof(team_t));
    nw->len = 0;
    nw->size = team_count;
    return nw;
}

void free_teams(teams_t *this)
{
    va_free(2, this->data, this);
}
