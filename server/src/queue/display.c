/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** display
*/

#include <stdlib.h>

#include "command.h"
#include "queue.h"

void queue_display(queue_t *q, void (*f)(command_t *))
{
    struct queue_node_s *tmp = q->node;

    for (size_t i = 0; i < q->len; i++) {
        f(&q->node->command);
        tmp = tmp->next;
    }
}
