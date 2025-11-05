//
// Created by milo on 11/4/25.
//

#ifndef PACMAN_COIN_H
#define PACMAN_COIN_H
#include "Subject.h"
#include <SFML/System/Vector2.hpp>

namespace logic {
class CoinModel : public Subject {
    sf::Vector2f position;

public:
    CoinModel() = default;

    [[nodiscard]] sf::Vector2f get_position() const { return position; }
    void set_position(const sf::Vector2f& pos) { this->position = pos; }
};
} // namespace logic

#endif // PACMAN_COIN_H
