//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_PAUSEDSTATE_H
#define PACMAN_PAUSEDSTATE_H
#include "State.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace representation {
class PausedState final : public State {
    sf::RectangleShape menu_button;
    sf::RectangleShape resume_button;

public:
    explicit PausedState(StateManager& sm) : State(sm) {}
    void proces_user_input(const sf::Event&, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
};
} // namespace representation
#endif // PACMAN_PAUSEDSTATE_H
