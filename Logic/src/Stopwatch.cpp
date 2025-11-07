//
// Created by milod on 30/10/2025.
//

#include "../include/Stopwatch.h"

logic::Stopwatch* logic::Stopwatch::stopwatch_ = nullptr;

logic::Stopwatch* logic::Stopwatch::create() {
    if (stopwatch_ == nullptr) {
        stopwatch_ = new Stopwatch();
    }
    return stopwatch_;
}

logic::Stopwatch::Stopwatch() {
    t_start = std::chrono::high_resolution_clock::now();
    t_previous = t_start;
}

double logic::Stopwatch::get_delta_time() {
    std::chrono::system_clock::time_point now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> delta = now - t_previous;  // verschil in milliseconden
    t_previous = now;
    return delta.count();
}


/*
double logic::Stopwatch::get_start_time() {
    std::chrono::system_clock::time_point now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> delta = now - t_start;  // verschil in milliseconden
    return delta.count();
}*/