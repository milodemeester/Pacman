//
// Created by milo on 11/1/25.
//

#include "../include/LevelState.h"
#include "../include/PausedState.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include <iostream>

LevelState::LevelState() {
     World* w = new World();
     world = w;
}

std::pair<bool, State*> LevelState::proces_user_input(const sf::Event* event, StateFactory* state_factory) {
    std::pair<bool,State*> output;
    output.first = false;
    output.second = nullptr;
    if (event->is<sf::Event::KeyPressed>()) {
        auto pressed = event->getIf<sf::Event::KeyPressed>();
        auto key = pressed->code;
        if (key == sf::Keyboard::Key::Escape) {
            PausedState* paused_state = state_factory->create_paused_state();
            output.second = paused_state;
        }
    }
    return output;
}


void LevelState::render(sf::RenderWindow* window) {
    sf::Font font;
    if (!font.openFromFile("../data/CrackMan.TTF")) {
        std::cerr << "Failed to load font." << std::endl;
    }
    sf::Text text(font);
    text.setString("LEVELSTATE");
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

void LevelState::update(double delta_time, Score score) {
    world->update(delta_time, score);
}
