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
    std::chrono::system_clock::time_point initialize_time;
    double wait_time = 0;
    bool chasing_mode = false; // false = fear mode, true = chasing mode
public:
    GhostModel(Coordinate pos, Direction dir, int world_width, int world_height);
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
