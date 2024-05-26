/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** team
*/

#pragma once

#include <stdbool.h>
#include "types/team.h"

/**
 * @brief resize the teams vector
 *
 * @param v the teams vector
 * @return true if success, false if error
 */
bool resize_vector_team(teams_t *v);

/**
 * @brief push back a team in the teams vector
 *
 * @param v the teams vector
 * @param nw the team to push back
 */
void push_back_vector_team(teams_t *v, const team_t *nw);

/**
 * @brief Create a team object
 *
 * @param name the name of the team
 * @return team_t the created team
 */
team_t create_team(char const *name);

/**
 * @brief Initialize the teams vector
 *
 * @param team_count the base size
 * @return teams_t * the initialized teams vector
 */
teams_t *init_teams(size_t team_count);
