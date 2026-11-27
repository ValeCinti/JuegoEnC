// Esto en consola para correr:
// cmake --build build; if ($?) { .\build\forja_cero.exe }


#include <stdio.h>
#include "core/arena.h"
#include "core/clock.h"
#include "raylib.h"

#define ARENA_PERM_SIZE  (64 * 1024 * 1024)   // 64 MB - datos que se cargan al arrancar y viven todo el juego (ítems, recetas, configuración).
#define ARENA_FRAME_SIZE (4 * 1024 * 1024)    // 4 MB -  memoria temporal que se borra en cada frame (textos de UI, listas y cálculos del momento).

typedef enum {
    STATE_MENU,
    STATE_PLAYING,
    STATE_PAUSED
} GameState;

int main(void) {
    Arena permanente, frame;
    if (!arena_init(&permanente, ARENA_PERM_SIZE)) return 1;
    if (!arena_init(&frame, ARENA_FRAME_SIZE))     return 1;


    const int screenWidth = 1920;
    const int screenHeight = 1080;


    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(screenWidth, screenHeight, "Forja Cero");
    SetExitKey(KEY_NULL);
    SetTargetFPS(100);

    GameClock clock;
    clock_init(&clock, GetTime());
    GameState estado = STATE_MENU;
    bool salir = false;

    while (!WindowShouldClose()) {
        arena_reset(&frame); 
        
        bool pausado = (estado != STATE_PLAYING);
        clock_begin_frame(&clock, GetTime(), pausado);

        switch (estado){

            case STATE_MENU:
                if (IsKeyPressed(KEY_ENTER)){
                    estado = STATE_PLAYING;
                }
                else if (IsKeyPressed(KEY_ESCAPE)){
                    salir = true;
                }
                break;

            case STATE_PLAYING:
                if (IsKeyPressed(KEY_ESCAPE)){
                    estado = STATE_PAUSED;
                    break;
                }

                if (clock_step_physics(&clock)) {
                    // mover jugador y cosas de fisica
                }
                if (clock_step_sim(&clock)) {
                    //mover maquinas, cintas etc
                }
                clock_compute_alphas(&clock);
                break;

            case STATE_PAUSED:
                if (IsKeyPressed(KEY_ESCAPE)){
                    estado = STATE_PLAYING;
                }
                else if (IsKeyPressed(KEY_M)){
                    estado = STATE_MENU;
                }
                break;
        }

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