//
// Created by milod on 30/10/2025.
//

#include "../include/Stopwatch.h"

namespace logic::core {
std::shared_ptr<Stopwatch> Stopwatch::getInstance() {
    if (stopwatch_ == nullptr) {
        stopwatch_ = std::shared_ptr<Stopwatch>(new Stopwatch());
    }
    return stopwatch_;
}

Stopwatch::Stopwatch() {
    t_start = std::chrono::high_resolution_clock::now();
    t_previous = t_start;
}

float Stopwatch::get_delta_time() {
    std::chrono::system_clock::time_point now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> delta = now - t_previous; // difference in milliseconds
    t_previous = now;
    return delta.count();
}

float Stopwatch::get_start_time() {
    std::chrono::system_clock::time_point now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> delta = now - t_start; // difference in milliseconds
    return delta.count();
}

float Stopwatch::get_time_between(std::chrono::system_clock::time_point time_point1,
                                          std::chrono::system_clock::time_point time_point2) {
    std::chrono::duration<float, std::milli> delta = time_point1 - time_point2;
    return delta.count();
}

std::chrono::system_clock::time_point Stopwatch::get_now() { return std::chrono::high_resolution_clock::now(); }
}