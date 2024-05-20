/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pop
*/

#include "command.h"
#include "queue.h"

command_t *queue_pop(queue_t *q)
{
    struct queue_node_s *node = q->node;
    command_t *tmp = {0};

    if (q->len == 0) {
        return NULL;
    }
    q->node = node->next;
    tmp = &node->command;
    free(node);
    return tmp;
}
