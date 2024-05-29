/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** utils
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Log a debug message
 *
 * @param fmt the format string
 * @param ... the arguments to replace the format string
 */
void logger_debug(char const *fmt, ...);

/**
 * @brief Log an info message
 *
 * @param fmt the format string
 * @param ... the arguments to replace the format string
 */
void logger_info(char const *fmt, ...);

/**
 * @brief Log a warning message
 *
 * @param fmt the format string
 * @param ... the arguments to replace the format string
 */
void logger_warn(char const *fmt, ...);

/**
 * @brief Log an error message
 *
 * @param fmt the format string
 * @param ... the arguments to replace the format string
 */
void logger_error(char const *fmt, ...);

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
