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

#define TYPE str_t *
#define NAME vector_str_t
#include "vector.h"

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

str_t *str_new(size_t size);
str_t *str_dup(str_t const *str);

void str_scadd(str_t *this, char const *s);
void str_sadd(str_t *this, str_t const *s);
char *str_cstr(str_t const *s);
struct vector_str_t *str_split(str_t *s, char *delim);
void str_free(str_t *s);
