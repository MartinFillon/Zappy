/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** buffer
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "str.h"

// Next step is putting a queue on request
typedef struct io_s {
    str_t *req;
    str_t *res;
    bool is_ready;
} io_t;
