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

representation::PausedState::PausedState(StateManager& sm, sf::Vector2u windowsize) : State(sm) {
    if (!font_.loadFromFile("../data/Font.TTF")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    // --- menu button ---
    menuButtontext_.setFont(font_);
    menuButtontext_.setFillColor(sf::Color::Black);
    menuButtontext_.setString("Back to menu");

    // --- menu button background ---
    menuButtonBackground_.setFillColor(sf::Color::Yellow);
    menuButtonBackground_.setOutlineColor(sf::Color::White);
    menuButtonBackground_.setOutlineThickness(1);

    // --- menu banner ---
    resumeButtonText_.setFont(font_);
    resumeButtonText_.setFillColor(sf::Color::Black);
    resumeButtonText_.setString("Resume");

    // background of the button
    resumeButtonBackground_.setFillColor(sf::Color::Yellow);
    resumeButtonBackground_.setOutlineColor(sf::Color::White);
    resumeButtonBackground_.setOutlineThickness(1);

    // --- score ---
    updateLayout(windowsize);
}

void representation::PausedState::updateLayout(sf::Vector2u windowSize) {
    // --- Menu Button ---
    unsigned int character_size = (windowSize.x / 32 + windowSize.y / 32); // TODO: make this dynamic
    menuButtontext_.setCharacterSize(character_size);
    sf::FloatRect textBounds = menuButtontext_.getLocalBounds();
    menuButtontext_.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    sf::Vector2f pos = {float(windowSize.x / 2 - 12), windowSize.y - float(character_size)};
    menuButtontext_.setPosition(pos);

    // De achtergrond heeft een andere grootte, dus we moeten de tekst herpositioneren
    menuButtonBackground_.setSize({character_size * 12.f, character_size * 2.f}); // Iets groter gemaakt voor padding
    menuButtonBackground_.setOrigin(menuButtonBackground_.getSize() / 2.f +  menuButtonBackground_.getGlobalBounds().getPosition());
    menuButtonBackground_.setPosition(pos);

    // --- Menu Banner ---
    unsigned int character_size2 = (windowSize.x / 32 + windowSize.y / 32);
    resumeButtonText_.setCharacterSize(character_size2);
    sf::FloatRect bannerTextBounds = resumeButtonText_.getLocalBounds();
    resumeButtonText_.setOrigin(bannerTextBounds.left + bannerTextBounds.width / 2.0f, bannerTextBounds.top + bannerTextBounds.height / 2.0f);
    sf::Vector2f pos2 = {float(windowSize.x / 2 - 12), windowSize.y - 2 * float(character_size2) - character_size2 * float(1.5)};
    resumeButtonText_.setPosition(pos2);

    resumeButtonBackground_.setSize({character_size2 * 6.f, character_size2 * 2.f});
    resumeButtonBackground_.setOrigin(resumeButtonBackground_.getSize() / 2.f +  resumeButtonBackground_.getGlobalBounds().getPosition());
    resumeButtonBackground_.setPosition(pos2);
}

void representation::PausedState::render(sf::RenderWindow& window) {
    window.draw(menuButtonBackground_);
    window.draw(resumeButtonBackground_);
    window.draw(menuButtontext_);
    window.draw(resumeButtonText_);
}

void representation::PausedState::proces_user_input(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouseWorld = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        auto bounds_resume = resumeButtonBackground_.getGlobalBounds();
        Coordinate upper_left_corner1(bounds_resume.left, bounds_resume.top);
        Coordinate lower_right_corner1(bounds_resume.left + bounds_resume.width,
                                       bounds_resume.top + bounds_resume.height);
        auto bounds_menu = menuButtonBackground_.getGlobalBounds();
        Coordinate upper_left_corner2(bounds_menu.left, bounds_menu.top);
        Coordinate lower_right_corner2(bounds_menu.left + bounds_menu.width, bounds_menu.top + bounds_menu.height);
        if (utils::contains(upper_left_corner1, lower_right_corner1, Coordinate(mouseWorld.x, mouseWorld.y))) {
            manager_.pop_state();
        } else if (utils::contains(upper_left_corner2, lower_right_corner2, Coordinate(mouseWorld.x, mouseWorld.y))) {
            manager_.double_pop_state();
        }
    }
}