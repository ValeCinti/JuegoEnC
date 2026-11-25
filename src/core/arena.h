#ifndef ARENA_H
#define ARENA_H
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    char* base;    // el bloque grande
    size_t size;    // tamaño total
    size_t offset;  // cuánto se usó
} Arena;

bool arena_init(Arena* a,  size_t size);
void* arena_alloc(Arena* a, size_t size);
void arena_reset(Arena* a);
void arena_free(Arena* a);


#endif