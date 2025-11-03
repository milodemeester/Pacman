//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_STOPWATCH_H
#define PACMAN_STOPWATCH_H
#include <chrono>

class Stopwatch{
    std::chrono::system_clock::time_point t_start;
    std::chrono::system_clock::time_point t_previous;
protected:
    static Stopwatch* stopwatch_;
    Stopwatch();
public:
    Stopwatch(Stopwatch& other) = delete;

    void operator=(const Stopwatch& other) = delete;

    static Stopwatch* create();

    double get_delta_time();
};


#endif //PACMAN_STOPWATCH_H