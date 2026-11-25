// Esto en consola para correr:
// cmake --build build; if ($?) { .\build\forja_cero.exe }


#include <stdio.h>
#include "raylib.h"

#include "core/logs.h"

int main(void) {
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Forja Cero");
    SetTargetFPS(120);

    while (!WindowShouldClose()) {
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
    return 0;
}