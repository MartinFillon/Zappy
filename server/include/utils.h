/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** utils
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include "core/types/ai.h"
#include "core/types/client.h"
#include "core/types/position.h"

/**
 * @brief frees a double char array
 *
 * @param arr the array to free
 */
void my_free_box(char **arr);

/**
 * @brief frees a set number of pointers
 *
 * @param nb the number of pointers to free
 * @param ... the pointers to free
 */
void va_free(int nb, ...);

int modulo(int nb, int m);

/**
 * @brief Check if there is not any args
 *
 * @param arg the string parameter to check
 * @return true if string is empty
 */
bool is_empty(char const *arg);

/**
 * @brief Check @param str is a number
 *
 * @param str the string parameter to check
 * @return true if string is empty
 */
bool is_number(char const *str);

/**
 * @brief Compare if 2 positions are equals
 *
 * @param this Position1 to compare
 * @param oth Position2 to compare
 * @return true if pos are equals
 */
bool is_coord_equal(pos_t *this, pos_t *oth);

/**
 * @brief freeze an ai and assign him @param id as his incant id
 *
 * @param ai The ai to freeze
 * @param id The id to set
 */
void freeze_ai(ai_t *ai, int id);

/**
 * @brief unfreeze an ai
 *
 * @param ai The ai to unfreeze
 */
void unfreeze_ai(ai_t *ai);

/************************************************************************
 * Those are vectors comparison functions used for vector functions that
 * needs predicate as parameter
 *
 * NOTE: Whenever you need to define a predicate put the prototype here.
 *************************************************************************/

/**
 * @brief Compare 2 integers
 *
 * @param a first integer
 * @param b second integer
 * @return `true` if equal else `false`
 */
bool cmp_int(int *a, int *b);

/**
 * @brief Compare 2 ais
 *
 * @param a first ai
 * @param b second ai
 * @return `true` if they are the same else `false`
 */
bool cmp_ais(ai_t **a, ai_t **b);

/**
 * @brief Compare 2 clients
 *
 * @param a first client
 * @param b second client
 * @return `true` if they are the same else `false`
 */
bool cmp_cli(struct client_s *a, struct client_s *b);
