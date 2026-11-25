#include "clock.h"

void clock_init(GameClock *clock, double now_seconds) {
    clock->prev_time  = now_seconds;
    clock->frame_dt   = 0.0;
    clock->phys_accum = 0.0;
    clock->sim_accum  = 0.0;
    clock->alpha_phys = 0.0;
    clock->alpha_sim  = 0.0;
    clock->phys_ticks = 0;
    clock->sim_ticks  = 0;
}

void clock_begin_frame(GameClock *clock, double now_seconds, bool paused) {
    double raw_dt = now_seconds - clock->prev_time;
    clock->prev_time = now_seconds;

    if (raw_dt < 0.0) {
        raw_dt = 0.0;
    } else if (raw_dt > FC_MAX_FRAME_DT) {
        raw_dt = FC_MAX_FRAME_DT;
    }

    clock->frame_dt = raw_dt;

    if (!paused) {
        clock->phys_accum += raw_dt;
        clock->sim_accum  += raw_dt;
    }
}

bool clock_step_physics(GameClock *clock) {
    if (clock->phys_accum >= FC_PHYS_DT) {
        clock->phys_accum -= FC_PHYS_DT;
        clock->phys_ticks++;
        return true;
    }
    return false;
}

bool clock_step_sim(GameClock *clock) {
    if (clock->sim_accum >= FC_SIM_DT) {
        clock->sim_accum -= FC_SIM_DT;
        clock->sim_ticks++;
        return true;
    }
    return false;
}

void clock_compute_alphas(GameClock *clock) {
    clock->alpha_phys = clock->phys_accum / FC_PHYS_DT;
    clock->alpha_sim  = clock->sim_accum  / FC_SIM_DT;
}