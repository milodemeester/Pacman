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
    std::chrono::system_clock::time_point initialize_time; // the time_point where this object was initialized
    double wait_time = 0; // the time the ghost has to wait before it can escape the center
    bool chasing_mode = false; // false = fear mode, true = chasing mode
public:
    // constructor
    GhostModel(Coordinate pos, Direction dir, int world_width, int world_height);

    /**
     * @brief takes care of the wait_time and puts chasing_mode on true if the wait_time is over
     * @param dt the delta time between this update and the update prior to this one
     */
    void update(float dt);
};

class BlinkyModel : public GhostModel {
public:
    BlinkyModel(Coordinate pos, Direction dir, int world_width, int world_height);
    void update(float dt, World& world) override;
};

class PinkyModel : public GhostModel {
public:
    PinkyModel(Coordinate pos, Direction dir, int world_width, int world_height);
    void update(float dt, World& world) override;
};

class ClydeModel : public GhostModel {
public:
    ClydeModel(Coordinate pos, Direction dir, int world_width, int world_height);
    void update(float dt, World& world) override;
};

} // namespace logic

#endif // PACMAN_GHOST_H
