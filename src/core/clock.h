#ifndef FC_CLOCK_H
#define FC_CLOCK_H

#include <stdbool.h>
#include <stdint.h>

#define FC_PHYS_HZ      60.0
#define FC_PHYS_DT      (1.0 / FC_PHYS_HZ)   // ~0.0166667 s

#define FC_SIM_HZ       20.0
#define FC_SIM_DT       (1.0 / FC_SIM_HZ)    //  0.0500000 s (50 ms)

// Evita la "spiral of death" si la ventana se traba o se pausa en el debugger
#define FC_MAX_FRAME_DT 0.25

typedef struct {
    double prev_time;
    double frame_dt;

    double phys_accum;
    double sim_accum;

    double alpha_phys;   // [0.0, 1.0) interpolación de física (60 Hz)
    double alpha_sim;    // [0.0, 1.0) interpolación de simulación (20 Hz)

    uint64_t phys_ticks; // Total de ticks de física ejecutados
    uint64_t sim_ticks;  // Total de ticks de fábrica ejecutados
} GameClock;

void clock_init(GameClock *clock, double now_seconds);

// Llamar una vez por frame. Si paused == true, avanza el reloj sin acumular ticks.
void clock_begin_frame(GameClock *clock, double now_seconds, bool paused);

bool clock_step_physics(GameClock *clock);
bool clock_step_sim(GameClock *clock);
void clock_compute_alphas(GameClock *clock);

#endif // FC_CLOCK_H