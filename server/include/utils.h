/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** utils
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include "types/ai.h"
#include "types/position.h"

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
 * @brief Parse a number from a string
 *
 * @param args the string to parse
 * @param n the number to store the result
 * @return true if success, false if error
 */
[[nodiscard]] bool parse_number(char *restrict args, long *restrict n);

/**
 * @brief Check if there is not any args
 *
 * @param arg the string parameter to check
 * @return true if string is empty
 */
bool is_empty(char const *arg);

/**
 * @brief Compare if 2 positions are equals
 *
 * @param this Position1 to compare
 * @param oth Position2 to compare
 * @return true if pos are equals
 */
bool is_coord_equal(pos_t *this, pos_t *oth);

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
 * @return true if equal else false
 */
bool cmp_int(int a, int b);

bool cmp_ais(ai_t a, ai_t b);
