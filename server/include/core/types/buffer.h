/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** buffer
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>

struct buffer_s {
    char *buffer;
    size_t size;
};

// Next step is putting a queue on request
typedef struct io_s {
    struct buffer_s req;
    struct buffer_s res;
    bool is_ready;
} io_t;
