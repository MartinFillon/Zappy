/*
** EPITECH PROJECT, 2024
** teams
** File description:
** main
*/

#pragma once

#include "json.h"
#include "str.h"

typedef struct {
    json_data_t *self;
    str_t *current_key;
    size_t index;
    str_t *data;
} json_parser_t;

/**
** @brief to be called when encountering a boolean
** @param the parser to use
**/
int parse_boolean(json_parser_t *p);

/**
** @brief to be called when encountering a number
** @param the parser to use
**/
int parse_number(json_parser_t *p);

/**
** @brief to be called when encountering a string
** @param the parser to use
**/
int parse_string(json_parser_t *p);

/**
** @brief to be called when encountering a valuen and starting point of the
** parser
** @param the parser to use
**/
int parse_value(json_parser_t *p);

/**
** @brief to be called when encountering an array
** @param the parser to use
**/
int parse_array(json_parser_t *p);

/**
** @brief to be called when encountering a json object
** @param the parser to use
**/
int parse_object(json_parser_t *p);

/**
** @brief retrieve the current char or -1 if its the end
** @param the parser to use
**/
int get(json_parser_t *p);

/**
** @brief retrieve the next char with get after advancing one
** @param the parser to use
**/
int next(json_parser_t *p);

/**
** @brief skip all whitespaces, line breaks, or tabs
** @param the parser to use
**/
int skip_whitespace(json_parser_t *p);

/**
** @brief append the current elem ot either the current object or the current
** array
** @param the parser to use
**/
int append_value(json_parser_t *p, json_data_t *elem);

/**
** @brief retrieve a json key
** @param the parser to use
**/
int parse_key(json_parser_t *p);
