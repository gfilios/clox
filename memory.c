//
// Created by Georg Filios on 30.12.21.
//
#include <stdlib.h>
#include <strings.h>
#include "memory.h"

void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    void *result = realloc(pointer, newSize);
    if (result == NULL) { exit(1); };
    return result;
}
