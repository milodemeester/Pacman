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

    // --- score ---
    updateLayout(windowsize);
}


void representation::MenuState::updateLayout(sf::Vector2u windowSize) {
    float window_width = windowSize.x;
    float window_height = windowSize.y;

    // --- Play Button ---
    unsigned int character_size = (window_width / 32 + window_height / 32);
    playButtonText_.setCharacterSize(character_size);
    sf::FloatRect textBounds = playButtonText_.getLocalBounds();
    playButtonText_.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    playButtonText_.setPosition({window_width / 2.f, window_height - float(character_size)});

    // De achtergrond heeft een andere grootte, dus we moeten de tekst herpositioneren
    playButtonBackground_.setSize({character_size * 5.f, character_size * 2.f}); // Iets groter gemaakt voor padding
    playButtonBackground_.setOrigin(playButtonBackground_.getSize() / 2.f);
    playButtonBackground_.setPosition({window_width / 2.f, window_height - float(character_size)});

    // --- Menu Banner ---
    unsigned int character_size2 = (window_width / 16 + window_height / 16);
    menuBannerText_.setCharacterSize(character_size2);
    sf::FloatRect bannerTextBounds = menuBannerText_.getLocalBounds();
    menuBannerText_.setOrigin(bannerTextBounds.left + bannerTextBounds.width / 2.0f, bannerTextBounds.top + bannerTextBounds.height / 2.0f);
    menuBannerText_.setPosition({window_width / 2.f, float(character_size2)});

    menuBannerBackground_.setSize({character_size2 * 6.f, character_size2 * 2.f});
    menuBannerBackground_.setOrigin(menuBannerBackground_.getSize() / 2.f);
    menuBannerBackground_.setPosition({window_width / 2.f, float(character_size2)});
}

void representation::MenuState::proces_user_input(const sf::Event& event, sf::RenderWindow& window) {
    switch (event.type) {
    case sf::Event::Resized: {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
        updateLayout({event.size.width, event.size.height});
    }
    case sf::Event::MouseButtonPressed: {
        sf::Vector2f mouseWorld = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        auto bounds = playButtonBackground_.getGlobalBounds();
        Coordinate upper_left_corner(bounds.left, bounds.top);
        Coordinate lower_right_corner(bounds.left + bounds.width, bounds.top + bounds.height);
        if (utils::contains(upper_left_corner, lower_right_corner, Coordinate(mouseWorld.x, mouseWorld.y))) {
            std::unique_ptr<LevelState> level = std::make_unique<LevelState>(manager_, window.getSize());
            manager_.push_state(std::move(level));
        }
    }
    default:;
    }
}

void representation::MenuState::render(sf::RenderWindow& window) {
    window.draw(playButtonBackground_);
    window.draw(menuBannerBackground_);
    window.draw(playButtonText_);
    window.draw(menuBannerText_);
}