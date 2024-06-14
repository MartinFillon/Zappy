/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** loader
*/

#pragma once

#include "core/server.h"

typedef struct {
    bool (*loop)(zappy_t *, void *);
    void *(*init)(int);
    void (*destroy)(void *);
    void *handle;
} lib_t;

/**
 * @brief opens the displayers and loads it functions
 *
 * @param file the filename
 * @return lib_t all the data loaded by dhl
 */
lib_t open_dhl(char const *file);

/**
 * @brief closes and unload the displayer
 *
 * @param l the lib to unload
 */
void close_dhl(lib_t *l);
