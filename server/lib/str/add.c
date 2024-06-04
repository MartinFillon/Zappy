/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** add
*/

#include <string.h>
#include "str.h"

void str_scadd(str_t *this, char const *s)
{
    size_t len = strlen(s);

    if (this->size + len >= this->capacity) {
        str_resize(this);
        return str_scadd(this, s);
    }
    memcpy(this->data + this->size, s, len);
    this->size += len;
}

void str_sadd(str_t *this, str_t const *s)
{
    str_scadd(this, s->data);
}
