//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H
#include "State.h"
#include "../../Utilities/utils.h"
#include <SFML/Graphics/RectangleShape.hpp>

class LevelState;

class MenuState final : public State{
    sf::RectangleShape button;
public:
    std::pair<int, std::unique_ptr<State>> proces_user_input(const sf::Event& event, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

};
#endif // PACMAN_MENUSTATE_H
