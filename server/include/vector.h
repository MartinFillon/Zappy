/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** vector
*/

#pragma once

#include "types/ai.h"
#include "types/game.h"

/**
 * @brief resize the ais vector
 *
 * @param v the ais vector
 * @return true if success, false if error
 */
bool resize_vector_ai(vector_ai_t *v);

/**
 * @brief push back an ai in the ais vector
 *
 * @param v the ais vector
 * @param nw the ai to push back
 */
void push_back_vector_ai(vector_ai_t *v, ai_t const *nw);
