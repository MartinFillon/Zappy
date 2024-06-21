/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** queue
*/

#ifndef QUEUE
    #define QUEUE

    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>

    #ifndef TYPE
        #define TYPE int
    #endif

    #define FN_NAME_INNER(x, t) x##_##t
    #define FN_NAME(x, t) FN_NAME_INNER(x, t)

    #ifndef NAME
        #define NAME FN_NAME(queue, TYPE)
    #endif

struct NAME {
    TYPE *data;
    size_t size;
    size_t capacity;
};

/**
** @brief creates a queue
** @param the initial capacity
**/
static inline struct NAME *FN_NAME(queue_create, NAME)(size_t capacity)
{
    struct NAME *vec =
        (struct NAME *)calloc(1, sizeof(struct NAME));

    vec->data = (TYPE *)calloc(capacity, sizeof(TYPE));
    vec->size = 0;
    vec->capacity = capacity;
    return vec;
}

/**
** @brief destroys a queue
** @param the queue to destroy
**/
static inline void FN_NAME(queue_destroy, NAME)(struct NAME *vec)
{
    free(vec->data);
    free(vec);
}

/**
** @brief push a new value at the end of the queue
** @param the queue to push into
** @param the elem to push
**/
static inline void FN_NAME(queue_pushback, NAME)(
    struct NAME *vec,
    TYPE elem
)
{
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->data = (TYPE *)realloc(vec->data, vec->capacity * sizeof(TYPE));
    }
    vec->data[vec->size] = elem;
    vec->size++;
}

/**
** @brief push a new value at the front of the queue queue
** @param the queue to push into
** @param the elem to push
**/
static inline void FN_NAME(queue_pushfront, NAME)(
    struct NAME *q,
    TYPE elem
)
{
    if (q->size == q->capacity) {
        q->capacity *= 2;
        q->data = (TYPE *)realloc(q->data, q->capacity * sizeof(TYPE));
    }
    memmove(q->data + 1, q->data, (q->size) * sizeof(TYPE));
    q->data[0] = elem;
    q->size++;
}

/**
** @brief remove first elem in a queue
** @param the queue to remove from
**/
static inline TYPE FN_NAME(queue_pop, NAME)(struct NAME *queue)
{
    TYPE elem = queue->data[0];

    memmove(queue->data, queue->data + 1, (queue->size - 1) * sizeof(TYPE));
    queue->size--;
    return elem;
}

/**
** @brief remove elem at index @param idx in a queue
** @param queue the queue to remove from
** @param idx the index of the element
**/
static inline bool FN_NAME(queue_erase_at, NAME)(
    struct NAME *queue,
    size_t idx
)
{
    if (idx >= queue->size) {
        return false;
    }
    memmove(
        &queue->data + idx,
        queue->data + (idx + 1),
        (queue->size - (idx + 1)) * sizeof(TYPE)
    );
    queue->size--;
    return true;
}


    #undef TYPE
    #undef NAME
    #undef QUEUE
#endif
