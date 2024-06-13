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

static void *load_function(char const *name, void *handle)
{
    void *f = dlsym(handle, name);
    char *error = dlerror();

    if (error) {
        logs(ERROR_LEVEL, "Error loading %s: %s\n", name, error);
        return NULL;
    }
    return f;
}

static lib_t error_case(char const *file)
{
    if (strcmp(file, "server/base.so") == 0)
        return (lib_t){NULL, NULL, NULL, NULL};
    return open_dhl("server/base.so");
}

lib_t open_dhl(char const *file)
{
    lib_t l = {0};

    l.handle = dlopen(file, RTLD_LAZY);
    if (!l.handle) {
        logs(ERROR_LEVEL, "Error loading lib %s: %s\n", file, dlerror());
        return error_case(file);
    }
    dlerror();
    l.loop =
        (bool (*)(zappy_t *, void *))load_function("server_runner", l.handle);
    l.init = (void *(*)(int))load_function("init", l.handle);
    l.destroy = (void (*)(void *))load_function("destroy_renderer", l.handle);
    if (l.loop == NULL || l.init == NULL || l.destroy == NULL) {
        close_dhl(&l);
        return error_case(file);
    }
    return l;
}

void close_dhl(lib_t *l)
{
    dlclose(l->handle);
}
