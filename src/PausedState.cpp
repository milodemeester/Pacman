//
// Created by milo on 11/1/25.
//

#include "../include/PausedState.h"

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

#include <iostream>

std::pair<bool, State*> PausedState::proces_user_input(const sf::Event* event, StateFactory* state_factory) {
    // sf::Keyboard::Key key = event->code;
    std::pair<bool,State*> output;
    output.first = false;
    output.second = nullptr;
    /*if (key == sf::Keyboard::Key::M) { //TODO: this is not right, there should be an option, but for now it is M or L pressed
        output.first = true;
        output.second = state_factory->create_menu_state();
    }
    else if (key == sf::Keyboard::Key::L) {
        output.first = true;
        output.second = state_factory->create_level_state();
    }*/
    return output;
}

void PausedState::render(sf::RenderWindow* window) {
    sf::Font font;
    if (!font.openFromFile("../data/CrackMan.TTF")) {
        std::cerr << "Failed to load font." << std::endl;
    }
    sf::Text text(font);
    text.setString("PAUSED STATE");
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
