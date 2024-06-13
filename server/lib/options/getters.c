/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** getters
*/

#include <stdbool.h>
#include <stdlib.h>

#include "options/parser.h"

union data get_arg(struct args *args, char *name)
{
    for (size_t i = 0; i < args->size; i++) {
        if (strcmp(args->data[i].option->identifier, name) == 0) {
            return args->data[i].value;
        }
    }
    return (union data){0};
}
