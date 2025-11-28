//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_VICTORYSTATE_H
#define PACMAN_VICTORYSTATE_H
#include "State.h"

namespace representation {
class VictoryState final : public State {
    sf::Texture texture_;

    float btnLeft_;
    float btnTop_;
    float btnRight_;
    float btnBottom_;
public:
    explicit VictoryState(StateManager& sm);
    void proces_user_input(const sf::Event& event, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
};
} // namespace representation

#endif // PACMAN_VICTORYSTATE_H
