//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_VICTORYSTATE_H
#define PACMAN_VICTORYSTATE_H
#include "State.h"

namespace representation {
class VictoryState final : public State {
public:
    explicit VictoryState(StateManager sm) : State(sm) {}
    void proces_user_input(const sf::Event& event, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
};
} // namespace representation

#endif // PACMAN_VICTORYSTATE_H
