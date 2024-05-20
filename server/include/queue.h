/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** queue
*/

#pragma once

#include "command.h"

typedef struct queue_s {
    command_t *command;
    struct queue_s *next;
} queue_t;
