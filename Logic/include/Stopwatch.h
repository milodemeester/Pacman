//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_STOPWATCH_H
#define PACMAN_STOPWATCH_H
#include <chrono>
#include <memory>

namespace logic {
namespace core {
class Stopwatch {
    std::chrono::system_clock::time_point
        t_start; // the time_point the stopwatch was created (and thus the beginning of the game)
    std::chrono::system_clock::time_point t_previous; // the time_point of the previous "tick"
protected:
    inline static std::shared_ptr<Stopwatch> stopwatch_; // singleton instance

    // constructor
    Stopwatch();

public:
    // copy-constructor deleted for singleton-purpose
    Stopwatch(Stopwatch& other) = delete;

    // singleton-purpose
    void operator=(const Stopwatch& other) = delete;

    /**
     * @brief computes the time between now and the previous tick
     * @return delta time
     */
    float get_delta_time();

    /**
     * @brief computes the time between two time points
     * @param time_point1 the earliest time point
     * @param time_point2 the latest time point
     * @return the time between the two time points in milliseconds
     */
    float get_time_between(std::chrono::system_clock::time_point time_point1,
                           std::chrono::system_clock::time_point time_point2);

    // getters
    float get_start_time();
    std::chrono::system_clock::time_point get_now();
    static std::shared_ptr<Stopwatch> getInstance();
};
} // namespace core
} // namespace logic

#endif // PACMAN_STOPWATCH_H