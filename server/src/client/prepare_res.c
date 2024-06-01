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

#include "logger.h"
#include "macros.h"
#include "types/buffer.h"

static int fill_io(io_t *io, char *buff)
{
    io->res.size = strlen(buff) + 1;
    io->res.buffer = calloc(io->res.size, sizeof(char));
    if (!io->res.buffer) {
        logs(ERROR_LEVEL, "Allocation error on prepare response");
        return ERROR;
    }
    strcpy(io->res.buffer, buff);
    io->is_ready = true;
    return SUCCESS;
}

void prepare_response(io_t *io, char *fmt, ...)
{
    va_list args;
    char buff[BUFF_SIZE];

    va_start(args, fmt);
    if (vsprintf(buff, fmt, args) == ERROR) {
        logs(
            ERROR_LEVEL, "Unable to fill the buffer to prepare client response"
        );
        return;
    }
    va_end(args);
    fill_io(io, buff);
}

void prepare_response_cat(io_t *io, char *fmt, ...)
{
    va_list args;
    char buff[BUFF_SIZE];

    va_start(args, fmt);
    if (vsprintf(buff, fmt, args) == ERROR) {
        logs(
            ERROR_LEVEL, "Unable to fill the buffer to prepare client response"
        );
    }
    va_end(args);
    if (io->res.buffer == NULL) {
        fill_io(io, buff);
    } else {
        io->res.size = strlen(io->res.buffer) + strlen(buff) + 1;
        io->res.buffer =
            reallocarray(io->res.buffer, io->res.size, sizeof(char));
        strcat(io->res.buffer, buff);
        io->is_ready = true;
    }
}
