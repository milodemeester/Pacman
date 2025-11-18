//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "../../Utilities/utils.h"
#include "Direction.h"
#include "Subject.h"
#include <string>
#include <utility>

namespace logic {
enum class GhostType {
    Inky,
    Blinky,
    Pinky,
    Clyde
};
class GhostModel : public Subject {
    GhostType type_;
    double wait_time;
    bool chasing_mode = false;
public:
    GhostModel() : type_(GhostType::Inky), wait_time(0), Subject(Coordinate({0,0}), Direction::East) {};
    GhostModel(Coordinate pos, Direction dir, GhostType ghost_type);
    void update(float dt);

    [[nodiscard]] Coordinate get_position() const { return position; }
    [[nodiscard]] Direction get_direction() const { return direction; }

    void set_position(const Coordinate& pos) { this->position = pos; }
    void set_direction(Direction dir) { this->direction = dir; }
};
} // namespace logic

#endif // PACMAN_GHOST_H
