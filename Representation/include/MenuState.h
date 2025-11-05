//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H
#include <SFML/Graphics/RectangleShape.hpp>
#include "State.h"

namespace representation {
class MenuState final : public State {
    sf::RectangleShape button;

public:
    explicit MenuState(StateManager sm) : State(sm) {}
    void proces_user_input(const sf::Event& event, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
};
} // namespace representation

#endif // PACMAN_MENUSTATE_H
