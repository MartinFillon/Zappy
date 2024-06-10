/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** vec_cmp
*/

#include <stdbool.h>
#include "core/types/ai.h"

bool cmp_int(int a, int b)
{
    return a == b;
}

bool cmp_ais(ai_t a, ai_t b)
{
    return a.id == b.id;
}
