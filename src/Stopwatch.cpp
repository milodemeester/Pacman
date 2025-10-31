//
// Created by milod on 30/10/2025.
//

#include "../include/Stopwatch.h"

Stopwatch::Stopwatch() {
    t_start = std::chrono::high_resolution_clock::now();
    t_previous = t_start;
}

double Stopwatch::get_delta_time() {
    std::chrono::system_clock::time_point now = std::chrono::high_resolution_clock::now();
    double delta_time = (now-t_previous).count();
    t_previous = now;
    return delta_time;
}
