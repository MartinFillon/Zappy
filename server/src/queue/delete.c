/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** delete
*/

#include "queue.h"

void free_queue(queue_t *q)
{
    struct queue_node_s *tmp = NULL;

    for (size_t i = 0; i < q->len; i++) {
        tmp = q->node;
        q->node = tmp->next;
        free(tmp);
    }
    free(q);
}
