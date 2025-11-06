//
// Created by milo on 11/1/25.
//

#include "../include/PausedState.h"
#include "../../Utilities/utils.h"
#include "SFML/Graphics/Text.hpp"
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../include/StateManager.h"

void representation::PausedState::proces_user_input(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouseWorld = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        auto bounds_resume = resume_button.getGlobalBounds();
        Coordinate upper_left_corner1(bounds_resume.left, bounds_resume.top);
        Coordinate lower_right_corner1(bounds_resume.left + bounds_resume.width,
                                       bounds_resume.top + bounds_resume.height);
        auto bounds_menu = menu_button.getGlobalBounds();
        Coordinate upper_left_corner2(bounds_menu.left, bounds_menu.top);
        Coordinate lower_right_corner2(bounds_menu.left + bounds_menu.width, bounds_menu.top + bounds_menu.height);
        if (utils::contains(upper_left_corner1, lower_right_corner1, Coordinate(mouseWorld.x, mouseWorld.y))) {
            manager_.pop_state();
        } else if (utils::contains(upper_left_corner2, lower_right_corner2, Coordinate(mouseWorld.x, mouseWorld.y))) {
            manager_.pop_state();
            manager_.pop_state();
        }
    }
}

void representation::PausedState::render(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("../data/Font.TTF")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    // --- menu button ---
    std::string str = "Back to menu";
    unsigned int character_size = (window.getSize().x / 32 + window.getSize().y / 32); // TODO: make this dynamic
    sf::Text text(str, font, character_size);
    text.setFillColor(sf::Color::Black);
    sf::Vector2u window_size = window.getSize();
    float window_width = window_size.x;
    float window_height = window_size.y;
    text.setOrigin(text.getGlobalBounds().getSize() / 2.f +
                   text.getLocalBounds().getPosition()); // set origin to center of the text
    text.setPosition({window_width / 2 - 12, window_height - 2 * float(character_size) -
                                                 character_size}); // set position of the text to center of screen

    // background of the button
    sf::RectangleShape background = sf::RectangleShape();
    background.setFillColor(sf::Color::Yellow);
    background.setSize(sf::Vector2f(character_size * 10, character_size));
    background.setOrigin(background.getGlobalBounds().getSize() / 2.f + background.getGlobalBounds().getPosition());
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(1);
    background.setPosition({window_width / 2 - 12, window_height - 2 * float(character_size) - character_size});
    window.draw(background);
    window.draw(text);
    menu_button = background;

    // --- resume button ---
    std::string str2 = "Resume";
    unsigned int character_size2 = (window.getSize().x / 32 + window.getSize().y / 32); // TODO: make this dynamic
    sf::Text text2(str2, font, character_size2);
    text2.setFillColor(sf::Color::Black);
    sf::Vector2u window_size2 = window.getSize();
    float window_width2 = window_size2.x;
    float window_height2 = window_size2.y;
    text2.setOrigin(text2.getGlobalBounds().getSize() / 2.f +
                    text2.getLocalBounds().getPosition()); // set origin to center of the text
    text2.setPosition({window_width2 / 2 - 12,
                       window_height2 - float(character_size2)}); // set position of the text to center of screen

    // background of the button
    sf::RectangleShape background2 = sf::RectangleShape();
    background2.setFillColor(sf::Color::Yellow);
    background2.setSize(sf::Vector2f(character_size2 * 10, character_size2));
    background2.setOrigin(background2.getGlobalBounds().getSize() / 2.f + background2.getGlobalBounds().getPosition());
    background2.setOutlineColor(sf::Color::White);
    background2.setOutlineThickness(1);
    background2.setPosition({window_width2 / 2 - 12, window_height2 - float(character_size2)});
    window.draw(background2);
    window.draw(text2);
    resume_button = background2;
}
