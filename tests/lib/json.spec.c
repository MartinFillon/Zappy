/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** json.spec
*/

#include "json/json.h"

#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect(void);

Test(json, parse_simple_json)
{
    str_t *str = str_snew("{\"key\": \"value\"}");
    json_data_t *data = json_parse(str);
    cr_assert_not_null(data);

    str_t *key = str_snew("key");
    str_t *value = json_get_string(data, key);
    cr_assert_str_eq(value->data, "value");
    json_free(data);
}

Test(json, parse_json_string_with_escape)
{
    str_t *str = str_snew("{\"key\": \"\\rva\\lue\\n\\t\"}");
    json_data_t *data = json_parse(str);
    cr_assert_not_null(data);

    str_t *key = str_snew("key");
    str_t *value = json_get_string(data, key);
    cr_assert_str_eq(value->data, "\rvalue\n\t");
    json_free(data);
}

Test(json, parse_json_number)
{
    str_t *str = str_snew("{\"key\": 42}");
    json_data_t *data = json_parse(str);
    cr_assert_not_null(data);

    str_t *key = str_snew("key");
    int value = json_get_number(data, key);
    cr_assert_eq(value, 42);
    json_free(data);
}

Test(json, parse_json_negative_number)
{
    str_t *str = str_snew("{\"key\": -42}");
    json_data_t *data = json_parse(str);
    cr_assert_not_null(data);

    str_t *key = str_snew("key");
    int value = json_get_number(data, key);
    cr_assert_eq(value, -42);
    json_free(data);
}

Test(json, parse_json_float_number)
{
    str_t *str = str_snew("{\"key\": 42.42}");
    json_data_t *data = json_parse(str);
    cr_assert_not_null(data);

    str_t *key = str_snew("key");
    double value = json_get_number(data, key);
    cr_assert_eq(value, 42.42);
    json_free(data);
}

Test(json, parse_json_bool_true)
{
    str_t *str = str_snew("{\"key\": true}");
    json_data_t *data = json_parse(str);
    cr_assert_not_null(data);

    str_t *key = str_snew("key");
    bool value = json_get_bool(data, key);
    cr_assert_eq(value, true);
    json_free(data);
}

Test(json, parse_json_bool_false)
{
    str_t *str = str_snew("{\"key\": false}");
    json_data_t *data = json_parse(str);
    cr_assert_not_null(data);

    str_t *key = str_snew("key");
    bool value = json_get_bool(data, key);
    cr_assert_eq(value, false);
    json_free(data);
}

Test(json, parse_json_array)
{
    str_t *str = str_snew("{\"key\": [1, 2, 3]}");
    json_data_t *data = json_parse(str);
    cr_assert_not_null(data);

    str_t *key = str_snew("key");
    struct vec_json_t *array = json_get_array(data, key);
    cr_assert_not_null(array);

    cr_assert_eq(array->size, 3);
    cr_assert_eq(array->data[0]->t, NUMBER);
    cr_assert_eq(array->data[0]->data.num, 1);
    cr_assert_eq(array->data[1]->t, NUMBER);
    cr_assert_eq(array->data[1]->data.num, 2);
    cr_assert_eq(array->data[2]->t, NUMBER);
    cr_assert_eq(array->data[2]->data.num, 3);
    json_free(data);
}

Test(json, parse_json_object)
{
    str_t *str =
        str_snew("{\"key\": {\"subkey\": \"value\", \"subkey2\": 42}}");
    json_data_t *data = json_parse(str);
    cr_assert_not_null(data);

    str_t *key = str_snew("key");
    json_data_t subdata;
    subdata.data.obj = json_get_object(data, key);
    subdata.t = OBJECT;
    cr_assert_not_null(subdata.data.obj);

    str_t *subkey = str_snew("subkey");
    str_t *value = json_get_string(&subdata, subkey);
    cr_assert_str_eq(value->data, "value");
    str_t *subkey2 = str_snew("subkey2");
    double number = json_get_number(&subdata, subkey2);
    cr_assert_eq(number, 42);
    json_free(data);
}

Test(json, json_from_file)
{
    json_data_t *data = json_from_file("../../tests/lib/test.json");
    cr_assert_not_null(data);

    str_t *key = str_snew("key");
    str_t *value = json_get_string(data, key);
    cr_assert_str_eq(value->data, "value");
}

Test(json, json_from_file_not_found)
{
    json_data_t *data = json_from_file("notfound.json");
    cr_assert_null(data);
}

Test(json, json_free_null)
{
    json_free(NULL);
}

Test(json, json_dump_simple_json, .init = redirect)
{
    str_t *str = str_snew("{\"key\": \"value\"}");
    json_data_t *data = json_parse(str);
    cr_assert_not_null(data);

    print_json(1, data);
    cr_assert_stdout_eq_str("{\"key\":\"value\"\n}\n");
    json_free(data);
}

Test(json, json_dump_json_with_array, .init = redirect)
{
    str_t *str = str_snew("{\"key\": [1, 2, 3]}");
    json_data_t *data = json_parse(str);
    cr_assert_not_null(data);

    print_json(1, data);
    cr_assert_stdout_eq_str("{\"key\":[1.00\n,2.00\n,3.00\n]\n}\n");
    json_free(data);
}

Test(json, json_dump_number, .init = redirect)
{
    str_t *str = str_snew("{\"key\": 42}");
    json_data_t *data = json_parse(str);
    cr_assert_not_null(data);

    print_json(1, data);
    cr_assert_stdout_eq_str("{\"key\":42.00\n}\n");
    json_free(data);
}

Test(json, json_dump_bool, .init = redirect)
{
    str_t *str = str_snew("{\"key\": true}");
    json_data_t *data = json_parse(str);
    cr_assert_not_null(data);

    print_json(1, data);
    cr_assert_stdout_eq_str("{\"key\":true\n}\n");
    json_free(data);
}

Test(json, json_dump_object, .init = redirect)
{
    str_t *str =
        str_snew("{\"key\": {\"subkey\": \"value\", \"subkey2\": 42}}");
    json_data_t *data = json_parse(str);
    cr_assert_not_null(data);

    print_json(1, data);
    cr_assert_stdout_eq_str(
        "{\"key\":{\"subkey\":\"value\"\n,\"subkey2\":42.00\n}\n}\n");
    json_free(data);
}
