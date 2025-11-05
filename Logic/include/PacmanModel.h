//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H
#include "Direction.h"
#include "Subject.h"
#include <SFML/System/Vector2.hpp>
#include "../../Utilities/utils.h"

namespace logic {
class PacmanModel : public Subject {
    Coordinate position;
    Direction direction;

public:
    PacmanModel(Coordinate pos, Direction dir) : position(pos), direction(dir) {}
    void update(float dt);

    [[nodiscard]] Coordinate get_position() const { return position; }
    [[nodiscard]] Direction get_direction() const { return direction; }

    void set_position(const Coordinate& pos) { this->position = pos; }
    void set_direction(Direction dir) { this->direction = dir; }
};
} // namespace logic

#endif // PACMAN_PACMAN_H
