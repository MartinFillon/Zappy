/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** team
*/

#pragma once

#include <stdbool.h>
#include "types/team.h"

bool resize_vector_team(teams_t *v);
void push_back_vector_team(teams_t *v, const team_t *nw);
team_t create_team(char const *name);
