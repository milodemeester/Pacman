//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H
#include <SFML/Graphics/RectangleShape.hpp>
#include "State.h"
#include <SFML/Graphics/Text.hpp>

namespace representation {
class MenuState final : public State {
    void updateLayout(sf::Vector2u windowSize);
    sf::Font font_;
    sf::Text playButtonText_;
    sf::RectangleShape playButtonBackground_;
    sf::Text menuBannerText_;
    sf::RectangleShape menuBannerBackground_;

public:
    explicit MenuState(StateManager& sm,  sf::Vector2u windowsize);
    void proces_user_input(const sf::Event& event, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
};
} // namespace representation

#endif // PACMAN_MENUSTATE_H
