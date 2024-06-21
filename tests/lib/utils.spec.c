/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** utils.spec
*/

#include <criterion/criterion.h>
#include "core/types/ai.h"
#include "core/types/client.h"
#include <criterion/internal/assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"

Test(utils, test_my_free_box_arr)
{
    char **arr = malloc(sizeof(char *) * 10);

    arr[0] = NULL;
    my_free_box(arr);
}

Test(utils, test_my_free_box_big_arr)
{
    char **arr = malloc(sizeof(char *) * 10);

    arr[0] = strdup("Hello");
    arr[1] = NULL;
    my_free_box(arr);
}

Test(utils, test_my_free_box_null)
{
    char **arr = NULL;

    my_free_box(arr);
}

Test(utils, test_freeze_ai)
{
    ai_t freezer = {0};
    ai_t to_freeze = {0};

    freezer.id = 42;
    freeze_ai(&to_freeze, freezer.id);
    cr_assert_eq(to_freeze.incant.is_incant, true);
    cr_assert_eq(to_freeze.incant.id_incant, freezer.id);
}

Test(utils, test_unfreeze_ai)
{
    ai_t freezer = {0};
    ai_t to_freeze = {0};

    freezer.id = 42;
    freeze_ai(&to_freeze, freezer.id);
    unfreeze_ai(&to_freeze);
    cr_assert_eq(to_freeze.incant.is_incant, false);
    cr_assert_eq(to_freeze.incant.id_incant, 0);
}

Test(utils, test_coord_equal)
{
    pos_t pos1 = {1, 2};
    pos_t pos2 = {1, 2};

    cr_assert_eq(is_coord_equal(&pos1, &pos2), true);
}

Test(utils, test_coord_not_equal)
{
    pos_t pos1 = {2, 1};
    pos_t pos2 = {1, 2};

    cr_assert_eq(is_coord_equal(&pos1, &pos2), false);
}

Test(utils, test_is_empty)
{
    char str[] = "";

    cr_assert_eq(is_empty(str), true);
}

Test(utils, test_is_not_empty)
{
    char str[] = "hello";

    cr_assert_eq(is_empty(str), false);
}

Test(utils, test_is_number)
{
    char str[] = "123456789";

    cr_assert_eq(is_number(str), true);
}

Test(utils, test_is_not_number_last_char)
{
    char str[] = "123456789u";

    cr_assert_eq(is_number(str), false);
}

Test(utils, test_is_not_number_middle_char)
{
    char str[] = "12Y3456789";

    cr_assert_eq(is_number(str), false);
}

Test(utils, test_is_not_number)
{
    char str[] = "uWuGang";

    cr_assert_eq(is_number(str), false);
}

Test(utils, test_modulo_positive)
{
    cr_assert_eq(modulo(10, 5), 0);
    cr_assert_eq(modulo(2, 5), 2);
    cr_assert_eq(modulo(5, 5), 0);
}

Test(utils, test_modulo_negative)
{
    cr_assert_eq(modulo(-2, 5), 3);
    cr_assert_eq(modulo(-1, 5), 4);
    cr_assert_eq(modulo(-5, 5), 0);
}

Test(utils, test_va_free)
{
    char *str = malloc(sizeof(char) * 10);
    int *ptr = malloc(sizeof(int));
    float *fptr = malloc(sizeof(float));

    va_free(3, str, ptr, fptr);
}

Test(utils, test_cmp_int)
{
    int a = 2;
    int b = 2;

    cr_assert_eq(cmp_int(&a, &b), true);
    a = 4;
    cr_assert_eq(cmp_int(&a, &b), false);
}

Test(utils, test_cmp_ais)
{
    ai_t *a = calloc(sizeof(ai_t), 1);
    ai_t *b = calloc(sizeof(ai_t), 1);

    a->id = 42;
    b->id = 42;
    cr_assert_eq(cmp_ais(&a, &b), true);
    a->id = 4;
    cr_assert_eq(cmp_ais(&a, &b), false);
}

Test(utils, test_cmp_clis)
{
    client_t a = {0};
    client_t b = {0};

    a.fd = 42;
    b.fd = 42;
    cr_assert_eq(cmp_cli(&a, &b), true);
    a.fd = 4;
    cr_assert_eq(cmp_cli(&a, &b), false);
}
