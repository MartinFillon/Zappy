/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** team
*/

#include <stdlib.h>
#include <string.h>

#include "core/types/team.h"
#include "logger.h"
#include "args_info.h"

team_t create_team(args_infos_t *args, char *name)
{
    team_t team = {0};
    egg_t *egg = NULL;

    team.name = strdup(name);
    team.eggs = queue_create_queue_egg_t(args->clients_nb);
    for (__auto_type i = 0; i < args->clients_nb; i++) {
        egg = create_egg(rand() % args->width, rand() % args->height);
        if (!egg)
            continue;
        queue_pushback_queue_egg_t(team.eggs, egg);
    }
    logs(INFO, "Inited team %s with %ld eggs\n", team.name, team.eggs->size);
    free(name);
    return team;
}

void destroy_team(team_t *team)
{
    logs(INFO, "Destroying team %s\n", team->name);
    free(team->name);
    for (size_t i = 0; i < team->eggs->size; i++)
        destroy_egg(team->eggs->data[i]);
    queue_destroy_queue_egg_t(team->eggs);
}
