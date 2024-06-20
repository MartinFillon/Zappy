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
 * @brief parses a string into json
 *
 * @param the string to parse
 * @return The JSON Object parsed
 */
json_data_t *json_parse(str_t *str);

/**
 * @brief Display an entire JSON Object to the file descriptor @param fd,
 *        @param json MUST be of type Object
 *
 * @param fd File descriptor to print in
 * @param json Json Object to display
 */
void print_json(const int fd, json_data_t const *json);

/**
 * @brief Display a JSON Data to the file descriptor @param fd
 *
 * @param fd File descriptor to print in
 * @param json Json Object to display
 */
void print_data(const int fd, json_data_t const *data);

/**
 * @brief Open a file specified with his filepath specified in @param path
 *        and transform his content into a JSON Object.
 *
 * @param path Filepath to the file to transform
 * @return JSON Object created
 */
json_data_t *json_from_file(const char *path);

/**
 * @brief Parse a file refered by the file descriptor @param fd
 *        to a JSON Object
 *
 * @param fd File descriptor to the file being transformed.
 * @return JSON Object created
 */
json_data_t *json_from_fd(const int fd);

/**
 * @brief Parse a string @param str and transform it into a JSON Object
 *
 * @param str String to transform.
 * @return JSON Object created
 */
json_data_t *json_from_str(const char *str);

/**
 * @brief Get the boolean value inside the JSON Object @param this
 *        at key @param key (`str_t`)
 *
 * @param this JSON Object where the value is searched.
 * @param key Key of the value.
 * @return The value to get
 */
bool json_get_bool(json_data_t const *this, str_t const *key);

/**
 * @brief Get the double value inside the JSON Object @param this
 *        at key @param key (`str_t`)
 *
 * @param this JSON Object where the value is searched.
 * @param key Key of the value.
 * @return The value to get
 */
double json_get_number(json_data_t const *this, str_t const *key);

/**
 * @brief Get the double value inside the JSON Object @param this
 *        at key @param rkey (`char const *`)
 *
 * @param this JSON Object where the value is searched.
 * @param key Key of the value.
 * @return The value to get
 */
double json_get_number_raw(json_data_t const *this, char const *rkey);

/**
 * @brief Get the string (str_t) value inside the JSON Object @param this
 *        at key @param key (`str_t`)
 *
 * @param this JSON Object where the value is searched.
 * @param key Key of the value.
 * @return The value to get
 */
str_t *json_get_string(json_data_t const *this, str_t const *key);

/**
 * @brief Get the array value inside the JSON Object @param this
 *        at key @param key (`str_t`)
 *
 * @param this JSON Object where the value is searched.
 * @param key Key of the value.
 * @return The value to get
 */
struct vec_json_t *json_get_array(json_data_t const *this, str_t const *key);

/**
 * @brief Get the JSON Object value inside the JSON Object @param this
 *        at key @param key (`str_t`)
 *
 * @param this JSON Object where the value is searched.
 * @param key Key of the value.
 * @return The value to get
 */
struct map_json_data_t *json_get_object(
    json_data_t const *this,
    str_t const *key
);

/**
 * @brief Free a JSON Object
 *
 * @param json The JSON Object to free
 */
void json_free(json_data_t *json);
