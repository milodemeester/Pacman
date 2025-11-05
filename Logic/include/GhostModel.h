//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_GHOST_H
#define PACMAN_GHOST_H
#include "Direction.h"
#include "Subject.h"
#include <SFML/System/Vector2.hpp>
#include <string>
#include <utility>

namespace logic {
class GhostModel : public Subject {
    sf::Vector2f position;
    Direction direction;

public:
    GhostModel() = default;
    void update(float dt);

    [[nodiscard]] sf::Vector2f get_position() const { return position; }
    [[nodiscard]] Direction get_direction() const { return direction; }

    void set_position(const sf::Vector2f& pos) { this->position = pos; }
    void set_direction(Direction dir) { this->direction = dir; }
};
} // namespace logic

#endif // PACMAN_GHOST_H
