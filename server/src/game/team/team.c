/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** team
*/

#include <string.h>

#include "types/team.h"

team_t create_team(char const *name)
{
    team_t team = {0};

    team.name = strdup(name);
    return team;
}
