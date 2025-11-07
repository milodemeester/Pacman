//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_STOPWATCH_H
#define PACMAN_STOPWATCH_H
#include <chrono>

namespace logic {
class Stopwatch {
protected:
    static Stopwatch* stopwatch_;
    Stopwatch();

private:
    std::chrono::system_clock::time_point t_start;
    std::chrono::system_clock::time_point t_previous;

public:
    Stopwatch(Stopwatch& other) = delete;

    void operator=(const Stopwatch& other) = delete;

    static Stopwatch* create();

    double get_delta_time();

    //double get_start_time();
};
} // namespace logic

#endif // PACMAN_STOPWATCH_H