/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** add
*/

#include <stdint.h>
#include <string.h>
#include "logger.h"
#include "str.h"

void str_scadd(str_t *this, char const *s)
{
    unsigned long long len = strlen(s);
    logs(ERROR_LEVEL, "%p\n", this);
    if ((unsigned long long)this->size + len > SIZE_MAX) {
        return str_clear(this);
    }
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
