/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** handle_eggs_info
*/

#include <stdio.h>
#include <unistd.h>

#include "types/team.h"
#include "zappy.h"

static void display_team_eggs(team_t *team)
{
    egg_t *egg = NULL;

    dprintf(1, "Team: %s\n", team->name);
    for (size_t k = 0; k < team->eggs->size; k++) {
        egg = team->eggs->data[k];
        dprintf(1, "\tEgg [%ld]: pos (%d, %d)\n",
            egg->id, egg->pos.y, egg->pos.x);
    }
}

void handle_display_eggs(zappy_t *serv)
{
    for (size_t i = 0; i < serv->game.teams->size; i++) {
        display_team_eggs(&serv->game.teams->data[i]);
    }
}
