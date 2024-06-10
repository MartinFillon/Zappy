/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** mod
*/

#include <stddef.h>

int modulo(int nb, int m)
{
    int res = nb % m;

    if (res < 0)
        return res + m;
    return res;
}
