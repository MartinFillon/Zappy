/*
** EPITECH PROJECT, 2024
** teams
** File description:
** main
*/

#pragma once
#include <stdlib.h>

typedef struct {
    char *data;
    size_t size;
    size_t capacity;
} str_t;

/**
** @brief create a str
** @param the base string to use as data
**/
str_t *str_snew(char const *data);

/**
** @brief resize a str to double its capacity
** @param the base string
**/
void str_resize(str_t *s);

/**
** @brief append a a char to the end of a str
** @param the base string
** @param the char to use
**/
void str_cadd(str_t *s, char const c);

/**
** @brief clears a str
** @param the base string to use as data
**/
void str_clear(str_t *s);

/**
** @brief compares two str
** @param the base string
** @param the other string
**/
int str_cmp(str_t const *this, str_t const *other);
