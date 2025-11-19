//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_STOPWATCH_H
#define PACMAN_STOPWATCH_H
#include <chrono>
#include <memory>

namespace logic {
class Stopwatch {
    std::chrono::system_clock::time_point t_start; // the time_point the stopwatch was created (and thus the beginning of the game)
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
     * @return the singleton instance
     */
    static std::shared_ptr<Stopwatch> getInstance();

    /**
     * @brief computes the time between now and the previous tick
     * @return double delta time
     */
    double get_delta_time();

    /**
     * @return the time point that the game was started
     */
    double get_start_time();

    /**
     * @return the now-time point
     */
    std::chrono::system_clock::time_point get_now();

    /**
     * @brief computes the time between two time points
     * @param time_point1 the earliest time point
     * @param time_point2 the latest time point
     * @return the time between the two time points in milliseconds
     */
    double get_time_between(std::chrono::system_clock::time_point time_point1,
                            std::chrono::system_clock::time_point time_point2);
};
} // namespace logic

#endif // PACMAN_STOPWATCH_H