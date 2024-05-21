/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** free_box
*/

#include <stdlib.h>

void my_free_box(char **arr)
{
    for (size_t i = 0; arr[i] != NULL; i++)
        free(arr[i]);
    if (arr)
        free(arr);
}
