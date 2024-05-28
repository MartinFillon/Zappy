/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** team
*/

#include <string.h>
#include "args_info.h"

#include "types/team.h"

team_t create_team(args_infos_t *args, char const *name)
{
    team_t team = {0};

    team.name = strdup(name);
    team.eggs = vec_create_vec_egg_t(args->clients_nb);
    for (__auto_type i = 0; i < args->clients_nb; i++)
        vec_pushback_vec_egg_t(team.eggs, create_egg(args));
    return team;
}
