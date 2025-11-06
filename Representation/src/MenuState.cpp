//
// Created by milo on 11/1/25.
//

#include "../include/MenuState.h"
#include "../include/LevelState.h"
#include "../include/StateManager.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include <iostream>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "../../Utilities/utils.h"
#include "../include/EntityView.h"

representation::MenuState::MenuState(StateManager& sm, sf::Vector2u windowsize) : State(sm) {
    if (!font_.loadFromFile("../data/Font.TTF")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    // --- play button ---
    playButtonText_.setFont(font_);
    playButtonText_.setFillColor(sf::Color::Black);
    playButtonText_.setString("Play");

    // --- play button background ---
    playButtonBackground_.setFillColor(sf::Color::White);
    playButtonBackground_.setOutlineColor(sf::Color::White);
    playButtonBackground_.setOutlineThickness(1);

    // --- menu banner ---
    menuBannerText_.setFont(font_);
    menuBannerText_.setFillColor(sf::Color::Black);
    menuBannerText_.setString("Menu");

    // background of the button
    menuBannerBackground_.setFillColor(sf::Color::Yellow);
    menuBannerBackground_.setOutlineColor(sf::Color::White);
    menuBannerBackground_.setOutlineThickness(1);

    updateLayout(windowsize);
}


void representation::MenuState::updateLayout(sf::Vector2u windowSize)
{
    float window_width = windowSize.x;
    float window_height = windowSize.y;

    // --- Play Button ---
    unsigned int character_size = (window_width / 32 + window_height / 32);
    playButtonText_.setCharacterSize(character_size);
    playButtonText_.setOrigin(playButtonText_.getGlobalBounds().getSize() / 2.f + playButtonText_.getLocalBounds().getPosition());
    playButtonText_.setPosition({window_width / 2.f, window_height - float(character_size)});

    playButtonBackground_.setSize({character_size * 10.f, float(character_size)});
    playButtonBackground_.setOrigin(playButtonBackground_.getGlobalBounds().getSize() / 2.f + playButtonBackground_.getGlobalBounds().getPosition());
    playButtonBackground_.setPosition({window_width / 2.f, window_height - float(character_size)});

    // --- Menu Banner ---
    unsigned int character_size2 = (window_width / 16 + window_height / 16);
    menuBannerText_.setCharacterSize(character_size2);
    menuBannerText_.setOrigin(menuBannerText_.getGlobalBounds().getSize() / 2.f + menuBannerText_.getLocalBounds().getPosition());
    menuBannerText_.setPosition({window_width / 2.f, float(character_size2)});

    menuBannerBackground_.setSize({character_size2 * 10.f, float(character_size2)});
    menuBannerBackground_.setOrigin(menuBannerBackground_.getGlobalBounds().getSize() / 2.f + menuBannerBackground_.getGlobalBounds().getPosition());
    menuBannerBackground_.setPosition({window_width / 2.f, float(character_size2)});
}

void representation::MenuState::proces_user_input(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Resized) {
        sf::Vector2u windowSize = window.getSize();
        updateLayout(windowSize);
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouseWorld = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        auto bounds = playButtonBackground_.getGlobalBounds();
        Coordinate upper_left_corner(bounds.left, bounds.top);
        Coordinate lower_right_corner(bounds.left + bounds.width, bounds.top + bounds.height);
        if (utils::contains(upper_left_corner, lower_right_corner, Coordinate(mouseWorld.x, mouseWorld.y))) {
            std::unique_ptr<LevelState> level = std::make_unique<LevelState>(manager_, window.getSize());
            manager_.push_state(std::move(level));
        }
    }
}

void representation::MenuState::render(sf::RenderWindow& window) {
    window.draw(playButtonBackground_);
    window.draw(menuBannerBackground_);
    window.draw(playButtonText_);
    window.draw(menuBannerText_);
}