//
// Created by milo on 11/1/25.
//

#include "../include/MenuState.h"
#include "../include/LevelState.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include <iostream>

std::pair<bool, State*> MenuState::proces_user_input(const sf::Event* event,sf::RenderWindow* window) {
    std::pair<bool,State*> output;
    output.first = false;
    output.second = nullptr;
    if (event->type == sf::Event::MouseButtonPressed) {
        auto bounds = button.getGlobalBounds();
        Coordinate upper_left_corner(bounds.left, bounds.top);
        Coordinate lower_right_corner(bounds.left+bounds.width, bounds.top-bounds.height);
        if (utils::contains(upper_left_corner, lower_right_corner, Coordinate(event->mouseButton.x, event->mouseButton.y))) {
            auto* level_state = new LevelState;
            output.first = true;
            output.second = level_state;
        }
    }
    return output;
}

void MenuState::render(sf::RenderWindow* window) {
    sf::Font font;
    if (!font.loadFromFile("../data/CrackMan.TTF")) {
        std::cerr << "Failed to load font." << std::endl;
    }
    std::string str = "Click to play";
    unsigned int character_size = (window->getSize().x/32 + window->getSize().y/32); // TODO: make this dynamic
    sf::Text text(str, font, character_size);
    text.setFillColor(sf::Color::Black);
    sf::Vector2u window_size = window->getSize();
    float window_width = window_size.x;
    float window_height = window_size.y;
    text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition()); // set origin to center of the text
    text.setPosition({window_width/2-12, window_height-float(character_size)}); // set position of the text to center of screen

    // background of the button
    sf::RectangleShape background =  sf::RectangleShape();
    background.setFillColor(sf::Color::Yellow);
    background.setSize(sf::Vector2f(character_size*10, character_size));
    background.setOrigin(background.getGlobalBounds().getSize() / 2.f + background.getGlobalBounds().getPosition());
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(1);
    background.setPosition({window_width/2-12, window_height-float(character_size)});
    window->draw(background);
    window->draw(text);
    button = background;
}