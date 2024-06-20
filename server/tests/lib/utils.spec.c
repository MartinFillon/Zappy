/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** utils.spec
*/

#include <criterion/criterion.h>
#include <stdlib.h>

#include "utils.h"

Test(utils, test_my_free_box_arr)
{
    char **arr = malloc(sizeof(char *) * 10);

    arr[0] = NULL;
    my_free_box(arr);
}

Test(utils, test_my_free_box_null)
{
    char **arr = NULL;

    my_free_box(arr);
}

