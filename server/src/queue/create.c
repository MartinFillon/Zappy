/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** create
*/

#include <stdlib.h>

#include "queue.h"

queue_t *new_queue(size_t size_max)
{
    queue_t *queue = calloc(1, sizeof(queue_t));

    if (queue == NULL)
        return NULL;
    queue->size_max = size_max;
    return queue;
}
