/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** is_number
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_number(char const *str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}
