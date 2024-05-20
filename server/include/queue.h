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
    command_t *command;
    struct queue_node_s *next;
};

typedef struct {
    struct queue_node_s *node;
    size_t size_max;
} queue_t;
