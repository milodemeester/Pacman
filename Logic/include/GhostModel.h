//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "../../Utilities/utils.h"
#include "Direction.h"
#include "Subject.h"

#include <chrono>
#include <string>
#include <utility>

namespace logic {
enum class GhostType { Inky, Blinky, Pinky, Clyde };

class GhostModel : public MoveableSubject {
protected:
    double speed_ = 0.005; // measured in pixel/ms
    double get_speed() override;

    /**
     * @brief computes all the directions that are not the current direction
     * @param dir the direction that the ghost is currently travelling in
     * @return a vector of directions
     */
    static std::vector<logic::Direction> get_other_direction(logic::Direction dir);

    /**
     * @brief computes the opposite direction of the direction that the ghost is currently travelling at
     * @param dir the direction that the ghost is currently travelling in
     * @return a direction
     */
    static logic::Direction get_opposite_direction(logic::Direction dir);

    std::chrono::system_clock::time_point initialize_time; // the time_point where this object was initialized
    double wait_time = 0; // the time the ghost has to wait before it can escape the center
    bool chasing_mode = true; // false = fear mode, true = chasing mode
    bool waiting = true;
public:
    // constructor
    GhostModel(Coordinate pos, Direction dir, int world_width, int world_height);

    /**
     * @brief takes care of the wait_time and puts chasing_mode on true if the wait_time is over
     * @param dt the delta time between this update and the update prior to this one
     */
    void update(float dt);
};
}

#endif // PACMAN_GHOST_H
