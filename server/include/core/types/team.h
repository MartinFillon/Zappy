/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** team
*/

#pragma once

#include <stddef.h>
#include "core/types/position.h"
#include "args_info.h"

typedef struct {
    size_t id;
    pos_t pos;
} egg_t;

#define TYPE egg_t *
#define NAME queue_egg_t
#include "queue.h"

typedef struct {
    char *name;
    struct queue_egg_t *eggs;
} team_t;

/**
 * @brief Create a team with @param name and init all its eggs.
 *
 * @param args Command line arguments with the @param clients_nb
 *        for eggs creation.
 * @param name Name of the team to create.
 * @return The team created.
 */
team_t create_team(args_infos_t *args, char *name);

/**
 * @brief Create an egg set at coord ( @param x, @param y ).
 *
 * @param x X-axis coordinate.
 * @param y Y-axis coordinate.
 * @return The egg created.
 */
egg_t *create_egg(int x, int y);

/**
 * @brief Destroy a team specified in @param team.
 *
 * @param team The team to destroy.
 */
void destroy_team(team_t *team);

/**
 * @brief Destroy an egg specified in @param egg.
 *
 * @param egg The egg to destroy.
 */
void destroy_egg(egg_t *egg);
