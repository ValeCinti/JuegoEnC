#include <stdlib.h>
#include "arena.h"
#include "logs.h"

#define ARENA_ALIGN 8


/* Un Arena Allocator se encarga de reservar un gran bloque de memoria para despues ir dividiendose en bloques mas pequeños, esto permite que haya menos fragmentacion interna y lo vuelve mucho mas eficiente a la hora de allocar o deallocar en memoria. 
En caso de ser necesario se puede mejorar haciendo que el espacio de la Arena sea dinamica, para esto habria que hacerlo de forma especializada para Windows y Linux
*/

/* Inicializa la arena*/
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

/* Alloc asigna los nuevos espacios para los bloques que iran dentro de la arena. el inicio es una funcion para normalizar y que simpere la posicion en memoria sea multiplo de ARENA_ALIGN y asi ciertos tipos de datos puedan mas ser mas eficicentes. */
void *arena_alloc(Arena *a, size_t block_size) {
    size_t inicio = (a->offset + ARENA_ALIGN - 1) / ARENA_ALIGN * ARENA_ALIGN;

    if (inicio + block_size > a->size) {
        return NULL;
    }
    void *ptr = a->base + inicio;
    a->offset = inicio + block_size;
    return ptr;
}

/* Colocando el offset a 0, esencialmente estamos sobreescribiendo lo ya guardado y asi forzando un reset. */
void arena_reset(Arena *a) {
    a->offset = 0;
}


/* Arena Free: libera el espacio utilizado en memoria */
void arena_free(Arena *a) {
    free(a->base);
    a->base = NULL;
    a->size = 0;
    a->offset = 0;
}