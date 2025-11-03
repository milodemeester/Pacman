//
// Created by milo on 11/1/25.
//

#include "../include/MenuState.h"
#include "../include/LevelState.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include <iostream>
#include <memory>

std::pair<int, std::unique_ptr<State>> MenuState::proces_user_input(const sf::Event& event,sf::RenderWindow& window) {
    std::pair<int,std::unique_ptr<State>> output;
    output.first = 0;
    output.second = nullptr;
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouseWorld = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        auto bounds = button.getGlobalBounds();
        Coordinate upper_left_corner(bounds.left, bounds.top);
        Coordinate lower_right_corner(bounds.left + bounds.width, bounds.top + bounds.height);
        if (utils::contains(upper_left_corner, lower_right_corner, Coordinate(mouseWorld.x, mouseWorld.y))) {
            std::unique_ptr<LevelState> level_state = std::make_unique<LevelState>();
            output.second = std::move(level_state);
        }
    }
    return output;
}

void MenuState::render(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("../data/CrackMan.TTF")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    // --- play button ---
    std::string str = "PLAY";
    unsigned int character_size = (window.getSize().x/32 + window.getSize().y/32); // TODO: make this dynamic
    sf::Text text(str, font, character_size);
    text.setFillColor(sf::Color::Black);
    sf::Vector2u window_size = window.getSize();
    float window_width = window_size.x;
    float window_height = window_size.y;
    text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition()); // set origin to center of the text
    text.setPosition({window_width/2-12, window_height-float(character_size)}); // set position of the text to center of screen

    // background of the button
    sf::RectangleShape background =  sf::RectangleShape();
    background.setFillColor(sf::Color::White);
    background.setSize(sf::Vector2f(character_size*10, character_size));
    background.setOrigin(background.getGlobalBounds().getSize() / 2.f + background.getGlobalBounds().getPosition());
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(1);
    background.setPosition({window_width/2-12, window_height-float(character_size)});
    window.draw(background);
    window.draw(text);
    button = background;

    // --- Menu banner ---
    std::string str2 = "Menu";
    unsigned int character_size2 = (window.getSize().x/16 + window.getSize().y/16); // TODO: make this dynamic
    sf::Text text2(str2, font, character_size2);
    text2.setFillColor(sf::Color::Black);
    text2.setOrigin(text2.getGlobalBounds().getSize() / 2.f + text2.getLocalBounds().getPosition()); // set origin to center of the text
    text2.setPosition({window_width/2-12, float(character_size2)}); // set position of the text to center of screen

    // background of the button
    sf::RectangleShape background2 =  sf::RectangleShape();
    background2.setFillColor(sf::Color::Yellow);
    background2.setSize(sf::Vector2f(character_size2*10, character_size2));
    background2.setOrigin(background2.getGlobalBounds().getSize() / 2.f + background2.getGlobalBounds().getPosition());
    background2.setOutlineColor(sf::Color::White);
    background2.setOutlineThickness(1);
    background2.setPosition({window_width/2-12, float(character_size2)});
    window.draw(background2);
    window.draw(text2);
}