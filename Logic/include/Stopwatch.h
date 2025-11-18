//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_STOPWATCH_H
#define PACMAN_STOPWATCH_H
#include <chrono>

namespace logic {
class Stopwatch {
protected:
    inline static std::shared_ptr<Stopwatch> stopwatch_;
    Stopwatch();

private:
    std::chrono::system_clock::time_point t_start;
    std::chrono::system_clock::time_point t_previous;

public:
    Stopwatch(Stopwatch& other) = delete;

    void operator=(const Stopwatch& other) = delete;

    static std::shared_ptr<Stopwatch> getInstance();

    double get_delta_time();

    double get_start_time();

    std::chrono::system_clock::time_point get_now();

    double get_time_between(std::chrono::system_clock::time_point time_point1, std::chrono::system_clock::time_point time_point2);
};
} // namespace logic

#endif // PACMAN_STOPWATCH_H