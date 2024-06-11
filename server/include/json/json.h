/*
** EPITECH PROJECT, 2024
** teams
** File description:
** main
*/

#pragma once

#include <stdbool.h>

#include "str.h"

struct vec_json_t;
struct map_json_data_t;

typedef enum {
    NUMBER,
    OBJECT,
    ARRAY,
    BOOLEAN,
    STRING,
} types_t;

typedef union {
    struct vec_json_t *arr;
    struct map_json_data_t *obj;
    str_t *str;
    double num;
    bool boolean;
} json_type_t;

typedef struct {
    json_type_t data;
    types_t t;
} json_data_t;

#define TYPE json_data_t
#include "json/map.h"

#define TYPE json_data_t *
#define NAME vec_json_t
#include "vector.h"

/**
** @brief parses a string into json
** @param the string to parse
**/
json_data_t *json_parse(str_t *str);
void print_json(const int fd, json_data_t const *json);
void print_data(const int fd, json_data_t const *data);
bool validate_schema(json_data_t const *this, json_data_t const *schema);
json_data_t *json_from_file(const char *path);
json_data_t *json_from_fd(const int fd);
json_data_t *json_from_str(const char *str);

bool json_get_bool(json_data_t const *this, str_t const *key);
double json_get_number(json_data_t const *this, str_t const *key);
str_t *json_get_string(json_data_t const *this, str_t const *key);
struct vec_json_t *json_get_array(json_data_t const *this, str_t const *key);
struct map_json_data_t *json_get_object(
    json_data_t const *this,
    str_t const *key
);
void json_free(json_data_t *json);
double json_get_number_raw(json_data_t const *this, char const *rkey);
