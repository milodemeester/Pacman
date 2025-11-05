//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_WALLMODEL_H
#define PACMAN_WALLMODEL_H
#include "Subject.h"
#include <SFML/System/Vector2.hpp>

namespace logic {
class WallModel : public Subject {
    sf::Vector2f position;

public:
    WallModel() = default;

    [[nodiscard]] sf::Vector2f get_position() const { return position; }
    void set_position(const sf::Vector2f& pos) { this->position = pos; }
};
} // namespace logic
#endif // PACMAN_WALLMODEL_H
