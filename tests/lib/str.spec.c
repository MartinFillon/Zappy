/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** str.spec
*/

#include <criterion/criterion.h>

#include "str.h"

Test(str, test_str_new)
{
    str_t *str = str_new(10);
    cr_assert_eq(str->size, 0);
    cr_assert_eq(str->capacity, 10);
    str_free(str);
}

Test(str, test_str_snew)
{
    str_t *str = str_snew("Hello");
    cr_assert_str_eq(str->data, "Hello");
    cr_assert_eq(str->size, 5);
    cr_assert_eq(str->capacity, 5);
    str_free(str);
}

Test(str, test_str_dup)
{
    str_t *str = str_snew("Hello");
    str_t *str2 = str_dup(str);
    cr_assert_str_eq(str2->data, str->data);
    cr_assert_eq(str2->size, str->size);
    cr_assert_eq(str2->capacity, str->capacity);
    str_free(str);
    str_free(str2);
}

Test(str, test_str_append)
{
    str_t *str = str_snew("Hello");
    str_t *str2 = str_snew(" World");
    str_sadd(str, str2);
    cr_assert_str_eq(str->data, "Hello World");
    cr_assert_eq(str->size, 11);
    cr_assert_geq(str->capacity, 11);
    str_free(str);
    str_free(str2);
}

Test(str, test_str_append_c)
{
    str_t *str = str_snew("Hello");
    str_scadd(str, " World");
    cr_assert_str_eq(str->data, "Hello World");
    cr_assert_eq(str->size, 11);
    cr_assert_geq(str->capacity, 11);
    str_free(str);
}

Test(str, test_str_append_char)
{
    str_t *str = str_snew("Hello");
    str_cadd(str, '!');
    cr_assert_str_eq(str->data, "Hello!");
    cr_assert_eq(str->size, 6);
    cr_assert_geq(str->capacity, 6);
    str_free(str);
}

Test(str, test_str_cmp)
{
    str_t *str = str_snew("Hello");
    str_t *str2 = str_snew("Hello");
    cr_assert_eq(str_cmp(str, str2), 0);
    str_free(str);
    str_free(str2);
}

Test(str, test_str_cmp_fail)
{
    str_t *str = str_snew("Hello");
    str_t *str2 = str_snew("Hello World");
    cr_assert_neq(str_cmp(str, str2), 0);
    str_free(str);
    str_free(str2);
}

Test(str, test_str_snew_null)
{
    str_t *str = str_snew(NULL);
    cr_assert_null(str);
}

Test(str, str_clear)
{
    str_t *str = str_snew("Hello");
    str_clear(str);
    cr_assert_eq(str->size, 0);
    cr_assert_str_empty(str->data);
    str_free(str);
}

Test(str, str_toint)
{
    str_t *str = str_snew("42");
    long nb = 0;
    cr_assert(!str_toint(&nb, str));
    cr_assert_eq(nb, 42);
    str_free(str);
}

Test(str, str_toint_fail)
{
    str_t *str = str_snew("42a");
    long nb = 0;
    cr_assert(str_toint(&nb, str));
    str_free(str);
}

Test(str, str_cstr)
{
    str_t *str = str_snew("42.42");
    char *cstr = str_cstr(str);
    cr_assert_str_eq(cstr, "42.42");
    free(cstr);
    str_free(str);
}

Test(str, str_split)
{
    str_t *str = str_snew("Hello World");
    struct vector_str_t *tab = str_split(str, " ");
    cr_assert_eq(tab->size, 2);
    cr_assert_str_eq(tab->data[0]->data, "Hello");
    cr_assert_str_eq(tab->data[1]->data, "World");
    str_free(str);
    for (size_t i = 0; i < tab->size; i++)
        str_free(tab->data[i]);
    vec_destroy_vector_str_t(tab);
}

Test(str, str_join_base)
{
    str_t *str = str_snew("Hello World");
    struct vector_str_t *tab = str_split(str, " ");
    cr_assert_eq(tab->size, 2);
    cr_assert_str_eq(tab->data[0]->data, "Hello");
    cr_assert_str_eq(tab->data[1]->data, "World");
    str_t *joined = join_strs(tab, "!");
    cr_assert_str_eq(joined->data, "Hello!World");
    str_free(str);
}

Test(str, str_join_n_start)
{
    str_t *str = str_snew("Hello World");
    struct vector_str_t *tab = str_split(str, " ");
    cr_assert_eq(tab->size, 2);
    cr_assert_str_eq(tab->data[0]->data, "Hello");
    cr_assert_str_eq(tab->data[1]->data, "World");
    str_t *joined = join_n_start_strs(tab, "!", 1);
    cr_assert_str_eq(joined->data, "World");
    str_free(str);
}

Test(str, str_join_n_end)
{
    str_t *str = str_snew("Hello World");
    struct vector_str_t *tab = str_split(str, " ");
    cr_assert_eq(tab->size, 2);
    cr_assert_str_eq(tab->data[0]->data, "Hello");
    cr_assert_str_eq(tab->data[1]->data, "World");
    str_t *joined = join_n_end_strs(tab, "!", 1);
    cr_assert_str_eq(joined->data, "Hello");
    str_free(str);
}
