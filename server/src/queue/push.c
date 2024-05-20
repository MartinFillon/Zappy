/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** push
*/

#include <stdbool.h>
#include <stdlib.h>

#include "command.h"
#include "queue.h"

static enum queue_error_e internal_queue_push_back(queue_t *q, command_t *c)
{
    struct queue_node_s *new = calloc(1, sizeof(struct queue_node_s));
    struct queue_node_s *tmp = q->node;

    if (new == NULL)
        return QUEUE_ALLOC_FAILED;
    new->command = *c;
    new->next = NULL;
    for (size_t i = 0; i < q->len - 1; i++)
        tmp = tmp->next;
    tmp->next = new;
    q->len += 1;
    return QUEUE_SUCCESS;
}

enum queue_error_e queue_push_back(queue_t *q, command_t *command)
{
    if (q == NULL || command == NULL)
        return QUEUE_ALLOC_FAILED;
    if (q->len + 1 > q->size_max)
        return QUEUE_ERROR;
    return internal_queue_push_back(q, command);
}
