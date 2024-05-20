/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** queue
*/

#pragma once

#include <stdlib.h>
#include "command.h"

struct queue_node_s {
    command_t command;
    struct queue_node_s *next;
};

typedef struct {
    struct queue_node_s *node;
    size_t size_max;
    size_t len;
} queue_t;

/**
 * @brief creates a new queue with a max size specified
 *
 * @param size_max the max size of the queue
 * @return the new queue
 */
queue_t *new_queue(size_t size_max);

/**
 * @brief free a queue
 *
 * @param q the queue to free
 */
void free_queue(queue_t *q);
