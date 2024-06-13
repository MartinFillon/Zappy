/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** string
*/

#include <string.h>

#include "options/option.h"

union data convert_string(char const *arg)
{
    union data dt = {0};

    dt.string = strdup(arg);
    return dt;
}
