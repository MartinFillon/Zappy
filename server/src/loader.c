/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** loader
*/

#include <dlfcn.h>
#include <string.h>

#include "loader.h"
#include "logger.h"

lib_t open_dhl(char const *file)
{
    lib_t l = {0};
    char *error;

    l.handle = dlopen(file, RTLD_LAZY);
    if (!l.handle) {
        logs(ERROR_LEVEL, "%s\n", dlerror());
        if (strcmp(file, "base.so") == 0)
            return (lib_t){NULL, NULL, NULL};
        return open_dhl("base.so");
    }
    dlerror();
    l.loop = (bool (*)(zappy_t *, void *))dlsym(l.handle, "server_runner");
    l.init = (void *(*)(void))dlsym(l.handle, "init");
    error = dlerror();
    if (error) {
        logs(ERROR_LEVEL, "%s\n", dlerror());
        if (strcmp(file, "base.so") == 0)
            return (lib_t){NULL, NULL, NULL};
        return open_dhl("base.so");
    }
    return l;
}

void close_dhl(lib_t *l)
{
    dlclose(l->handle);
}
