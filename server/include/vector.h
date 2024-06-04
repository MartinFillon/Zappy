/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** vector
*/

#ifndef VECTOR
    #define VECTOR

    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>

    #ifndef TYPE
        #define TYPE int
    #endif

    #define FN_NAME_INNER(x, t) x##_##t
    #define FN_NAME(x, t) FN_NAME_INNER(x, t)

    #ifndef NAME
        #define NAME FN_NAME(vector, TYPE)
    #endif

struct NAME {
    TYPE *data;
    size_t size;
    size_t capacity;
};

/**
** @brief creates a vector
** @param the initial capacity
**/
static inline struct NAME *FN_NAME(vec_create, NAME)(size_t capacity)
{
    struct NAME *vec = (struct NAME *)calloc(1, sizeof(struct NAME));

    vec->data = (TYPE *)calloc(capacity, sizeof(TYPE));
    vec->size = 0;
    vec->capacity = capacity;
    return vec;
}

/**
** @brief destroys a vector
** @param the vector to destroy
**/
static inline void FN_NAME(vec_destroy, NAME)(struct NAME *vec)
{
    free(vec->data);
    free(vec);
}

/**
** @brief push a new value to a vector
** @param the vector to push into
** @param the elem to push
**/
static inline void FN_NAME(vec_pushback, NAME)(struct NAME *vec, TYPE elem)
{
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->data = (TYPE *)realloc(vec->data, vec->capacity * sizeof(TYPE));
    }
    vec->data[vec->size] = elem;
    vec->size++;
}

/**
** @brief remove last elem in a vector
** @param vec vector to remove from
**/
static inline void FN_NAME(vec_popback, NAME)(struct NAME *vec)
{
    vec->size--;
    memset(&vec->data[vec->size], 0, sizeof(TYPE));
}

/**
** @brief remove an element of the vector at the index @param idx
** @param vec vector where we will remove an element
** @param idx index of the element to be removed
** @return bool if the operation was successfull
**/
static inline bool FN_NAME(vec_erase_at, NAME)(struct NAME *vec, size_t idx)
{
    if (idx >= vec->size) {
        return false;
    }
    memmove(
        &vec->data + idx,
        vec->data + (idx + 1),
        (vec->size - (idx + 1)) * sizeof(TYPE)
    );
    vec->size--;
    return true;
}

/**
** @brief remove an element @param elem of the vector if it exist
** @param vec vector where we will remove an element
** @param elem element to be removed
** @param cmp comparison function used as predicate
**            to check which value to delete
** @return bool if the operation was successfull
**/
static inline bool FN_NAME(vec_erase, NAME)(
    struct NAME *vec,
    TYPE elem,
    bool (*cmp)(TYPE, TYPE)
)
{
    for (size_t i = 0; i < vec->size; i++) {
        if (cmp(vec->data[i], elem)) {
            return FN_NAME(vec_erase_at, NAME)(vec, i);
        }
    }
    return false;
}

/**
** @brief remove an element @param elem of the vector if it exist
** @param vec vector where we will remove an element
** @param elem element to be removed
** @param cmp comparison function used as predicate
**            to check which value to delete
** @return bool if the operation was successfull
**/
static inline void FN_NAME(vec_foreach, NAME)(
    struct NAME *vec,
    void (*func)(TYPE *)
)
{
    for (size_t i = 0; i < vec->size; i++) {
        func(vec->data + i);
    }
}

static inline void FN_NAME(vec_free, NAME)(
    struct NAME *vec,
    void (*free_func)(TYPE)
)
{
    for (__auto_type i = 0ul; i < vec->size; i++)
        if (free_func)
            free_func(vec->data[i]);
    FN_NAME(vec_destroy, NAME)(vec);
}

    #undef TYPE
    #undef NAME
    #undef VECTOR
#endif
