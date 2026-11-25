#include <stdlib.h>
#include "core/arena.h"
#include "core/logs.h"

#define ARENA_ALIGN 8

bool arena_init(Arena *a, size_t size) {
    a->base = malloc(size);
    if (a->base == NULL) {
        log_register(SY_LOG_ERROR, "No se pudo inicializar el Arena Allocator");
        a->size = 0;
        a->offset = 0;
        return false;
    }
    a->size = size;
    a->offset = 0;
    return true;
}

void *arena_alloc(Arena *a, size_t size) {
    size_t inicio = (a->offset + ARENA_ALIGN - 1) / ARENA_ALIGN * ARENA_ALIGN;
    if (inicio + size > a->size) {
        return NULL;
    }
    void *ptr = a->base + inicio;
    a->offset = inicio + size;
    return ptr;
}

void arena_reset(Arena *a) {
    a->offset = 0;
}

void arena_free(Arena *a) {
    free(a->base);
    a->base = NULL;
    a->size = 0;
    a->offset = 0;
}