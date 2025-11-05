//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H
#include "../../Utilities/utils.h"
#include "State.h"
#include <SFML/Graphics/RectangleShape.hpp>

class LevelState;

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
