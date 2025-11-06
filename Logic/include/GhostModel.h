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
class GhostModel : public Subject {
    Coordinate position;
    Direction direction;
public:
    GhostModel(Coordinate pos, Direction dir) : position(pos), direction(dir) {}
    GhostModel() = default;
    void update(float dt);

    [[nodiscard]] Coordinate get_position() const { return position; }
    [[nodiscard]] Direction get_direction() const { return direction; }

    void set_position(const Coordinate& pos) { this->position = pos; }
    void set_direction(Direction dir) { this->direction = dir; }
};
} // namespace logic

#endif // PACMAN_GHOST_H
