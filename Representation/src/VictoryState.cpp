//
// Created by milo on 11/1/25.
//

#include "../include/VictoryState.h"
#include "../include/LevelState.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include <iostream>
#include <memory>

void representation::VictoryState::proces_user_input(const sf::Event& event, sf::RenderWindow& window) {
    // sf::Keyboard::Key key = event->code;
}

void representation::VictoryState::render(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("../data/Font.TTF")) {
        std::cerr << "Failed to load font." << std::endl;
    }
    sf::Text text;
    text.setString("VICTORY STATE");
    float character_size = (window.getSize().x / 32 + window.getSize().y / 32); // TODO: make this dynamic
    text.setCharacterSize(character_size);
    text.setFillColor(sf::Color::Yellow);
    sf::Vector2u window_size = window.getSize();
    float window_width = window_size.x;
    float window_height = window_size.y;
    text.setOrigin(text.getGlobalBounds().getSize() / 2.f +
                   text.getLocalBounds().getPosition()); // set origin to center of the text
    text.setPosition(
        {window_width / 2 - 12, window_height - character_size}); // set position of the text to center of screen
    window.draw(text);
}
