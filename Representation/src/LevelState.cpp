//
// Created by milo on 11/1/25.
//

#include "../include/LevelState.h"
#include "../include/PausedState.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include <iostream>
#include "../../Logic/include/World.h"

LevelState::LevelState() {
     auto* w = new World(1920,1080);
     world = w;
}

std::pair<bool, State*> LevelState::proces_user_input(const sf::Event* event) {
    std::pair<bool,State*> output;
    output.first = false;
    output.second = nullptr;
    if (event->type == sf::Event::KeyPressed) {
        auto key = event->key;
        if (key.code == sf::Keyboard::Key::Escape) {
            auto* paused_state = new PausedState;
            output.second = paused_state;
        }
    }
    return output;
}


void LevelState::render(sf::RenderWindow* window) {
    sf::Font font;
    if (!font.loadFromFile("../data/CrackMan.TTF")) {
        std::cerr << "Failed to load font." << std::endl;
    }
    sf::Text text;
    text.setString("LEVELSTATE");
    float character_size = (window->getSize().x/32 + window->getSize().y/32); // TODO: make this dynamic
    text.setCharacterSize(character_size);
    text.setFillColor(sf::Color::Yellow);
    sf::Vector2u window_size = window->getSize();
    float window_width = window_size.x;
    float window_height = window_size.y;
    text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition()); // set origin to center of the text
    text.setPosition({window_width/2-12, window_height-character_size}); // set position of the text to center of screen
    window->draw(text);
}

void LevelState::update(double delta_time) {
    world->update(delta_time);
}
