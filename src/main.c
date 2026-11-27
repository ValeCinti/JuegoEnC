// Esto en consola para correr:
// cmake --build build; if ($?) { .\build\forja_cero.exe }


#include <stdio.h>
#include "core/arena.h"
#include "raylib.h"

#define ARENA_PERM_SIZE  (64 * 1024 * 1024)   // 64 MB - datos que se cargan al arrancar y viven todo el juego (ítems, recetas, configuración).
#define ARENA_FRAME_SIZE (4 * 1024 * 1024)    // 4 MB -  memoria temporal que se borra en cada frame (textos de UI, listas y cálculos del momento).

int main(void) {
    Arena permanente, frame;
    if (!arena_init(&permanente, ARENA_PERM_SIZE)) return 1;
    if (!arena_init(&frame, ARENA_FRAME_SIZE))     return 1;


    const int screenWidth = 1920;
    const int screenHeight = 1080;


    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(screenWidth, screenHeight, "Forja Cero");
    SetTargetFPS(100);

    while (!WindowShouldClose()) {
        arena_reset(&frame); 
        
        // --- UPDATE ---
        // Acá irá el fixed timestep (física 60 Hz y simulación 20 Hz)

        // --- RENDER ---
        BeginDrawing();
        ClearBackground((Color){ 18, 22, 28, 255 });

        DrawText("FORJA CERO - Ventana base funcionando", 20, 20, 24, RAYWHITE);
        DrawFPS(20, 60);
        EndDrawing();
    }

    CloseWindow();
    arena_free(&frame);
    arena_free(&permanente);
    return 0;
}