//
// Created by milo on 11/1/25.
//

#include "../include/MenuState.h"
#include "../include/LevelState.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "../include/StateFactory.h"
#include <iostream>

std::pair<bool, State*> MenuState::proces_user_input(const sf::Event* event, StateFactory* state_factory) {
    std::pair<bool,State*> output;
    output.first = false;
    output.second = nullptr;
    if (event->is<sf::Event::KeyPressed>()) {
        auto key_pressed = event->getIf<sf::Event::KeyPressed>();
        auto key = key_pressed->code;
        if (key == sf::Keyboard::Key::Enter) {
            LevelState* level_state = state_factory->create_level_state();
            output.first = true;
            output.second = level_state;
        }
    }
    return output;
}

void MenuState::render(sf::RenderWindow* window) {
    sf::Font font;
    if (!font.openFromFile("../data/CrackMan.TTF")) {
        std::cerr << "Failed to load font." << std::endl;
    }
    sf::Text text(font);
    text.setString("PRESS ENTER TO PLAY");
    float character_size = (window->getSize().x/32 + window->getSize().y/32); // TODO: make this dynamic
    text.setCharacterSize(character_size);
    text.setFillColor(sf::Color::Yellow);
    sf::Vector2u window_size = window->getSize();
    float window_width = window_size.x;
    float window_height = window_size.y;
    text.setOrigin(text.getGlobalBounds().size / 2.f + text.getLocalBounds().position); // set origin to center of the text
    text.setPosition({window_width/2-12, window_height-character_size}); // set position of the text to center of screen
    window->draw(text);
}