/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** file
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "json/json.h"
#include "str.h"

json_data_t *json_from_file(char const *file)
{
    int fd = open(file, O_RDONLY);
    json_data_t *res = NULL;

    if (fd == -1)
        return NULL;
    res = json_from_fd(fd);
    close(fd);
    return res;
}

json_data_t *json_from_fd(int fd)
{
    char *buff = calloc(1024, sizeof(char));
    char *s_buff = NULL;
    size_t s_size = 0;
    json_data_t *res = NULL;

    if (fd == -1)
        return NULL;
    while (read(fd, buff, 1024) > 0) {
        s_buff = realloc(s_buff, s_size + 1024);
        memcpy(s_buff + s_size, buff, 1024);
        s_size += 1024;
        memset(buff, 0, 1024);
    }
    res = json_from_str(s_buff);
    free(s_buff);
    free(buff);
    return res;
}

json_data_t *json_from_str(char const *str)
{
    json_data_t *res = NULL;
    str_t *s = str_snew(str);

    if (s == NULL)
        return NULL;
    res = json_parse(s);
    free(s->data);
    free(s);
    return res;
}
