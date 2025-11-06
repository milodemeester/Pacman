//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_PAUSEDSTATE_H
#define PACMAN_PAUSEDSTATE_H
#include "State.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace representation {
class PausedState final : public State {
    void updateLayout(sf::Vector2u windowSize);
    sf::Font font_;
    sf::Text menuButtontext_;
    sf::RectangleShape menuButtonBackground_;
    sf::Text resumeButtonText_;
    sf::RectangleShape resumeButtonBackground_;

public:
    PausedState(StateManager& sm, sf::Vector2u windowsize);
    void proces_user_input(const sf::Event&, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
};
} // namespace representation
#endif // PACMAN_PAUSEDSTATE_H
