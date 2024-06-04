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
    egg_t *egg = NULL;

    team.name = strdup(name);
    team.eggs = queue_create_queue_egg_t(args->clients_nb);
    for (__auto_type i = 0; i < args->clients_nb; i++) {
        egg = create_egg(args->width, args->height);
        if (!egg)
            continue;
        queue_pushback_queue_egg_t(team.eggs, egg);
    }
    return team;
}

void destroy_team(team_t *team)
{
    free(team->name);
    for (size_t i = 0; i < team->eggs->size; i++)
        destroy_egg(team->eggs->data[i]);
    queue_destroy_queue_egg_t(team->eggs);
}
