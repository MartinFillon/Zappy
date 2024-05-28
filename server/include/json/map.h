/*
** EPITECH PROJECT, 2024
** lib
** File description:
** map
*/

#ifndef MAP
    #define MAP

    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
    #include "str.h"

    #ifndef TYPE
        #define TYPE int
    #endif

    #define FN_NAME_INNER(x, t) x##_##t
    #define FN_NAME(x, t) FN_NAME_INNER(x, t)

    #define MAP_TYPE FN_NAME(map, TYPE)

    #define ELEM_TYPE FN_NAME(elem, TYPE)

struct ELEM_TYPE {
    TYPE *data;
    str_t *key;
};

struct MAP_TYPE {
    struct ELEM_TYPE *data;
    size_t size;
    size_t capacity;
};

/**
** @brief creates a map
** @param the initial capacity
**/
static inline struct MAP_TYPE *FN_NAME(map_create, TYPE)(size_t capacity)
{
    struct MAP_TYPE *vec = (struct MAP_TYPE *)malloc(sizeof(struct MAP_TYPE));

    vec->data = (struct ELEM_TYPE *)malloc(capacity * sizeof(TYPE));
    vec->size = 0;
    vec->capacity = capacity;
    return vec;
}

/**
** @brief push a new value to a map
** @param the map to push into
** @param the key to use
** @param the elem to push
**/
static inline void FN_NAME(map_push, TYPE)(
    struct MAP_TYPE *map,
    str_t *key,
    TYPE *data
)
{
    struct ELEM_TYPE elem = {0};

    if (map->size == map->capacity) {
        map->capacity *= 2;
        map->data = (struct ELEM_TYPE *)realloc(
            map->data, map->capacity * sizeof(struct ELEM_TYPE)
        );
    }
    for (size_t i = 0; i < map->size; i++) {
        if (str_cmp(map->data[i].key, key) == 0) {
            elem.data = data;
            return;
        }
    }
    elem.data = data;
    elem.key = key;
    map->data[map->size] = elem;
    map->size++;
}

/**
** @brief get a value from a map
** @param the map
** @param the key to search
**/
static inline TYPE *FN_NAME(map_get, TYPE)(
    struct MAP_TYPE const *map,
    str_t const *k
)
{
    for (size_t i = 0; i < map->size; i++) {
        if (str_cmp(k, map->data[i].key) == 0) {
            return map->data[i].data;
        }
    }
    return NULL;
}

    #undef TYPE
    #undef MAP
#endif
