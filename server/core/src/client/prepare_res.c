/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** prepare_res
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/types/buffer.h"

void prepare_response_cat(io_t *io, char *fmt, ...)
{
    va_list args;
    char *buff = NULL;

    va_start(args, fmt);
    vasprintf(&buff, fmt, args);
    va_end(args);
    str_scadd(io->res, buff);
    io->is_ready = true;
    free(buff);
}

void prepare_response_cat_va(io_t *io, char *fmt, va_list args)
{
    char *buff = NULL;

    vasprintf(&buff, fmt, args);
    str_scadd(io->res, buff);
    io->is_ready = true;
    free(buff);
}
