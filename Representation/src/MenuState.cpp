//
// Created by milo on 11/1/25.
//

#include "../include/MenuState.h"
#include "../../Utilities/utils.h"
#include "../include/EntityView.h"
#include "../include/LevelState.h"
#include "../include/StateManager.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>

representation::MenuState::MenuState(StateManager& sm, sf::Vector2u windowsize, std::shared_ptr<logic::Score> score) : State(sm), score_(std::move(score)) {
    if (!font_.loadFromFile("../data/fonts/pacman_font.TTF")) {
        std::cerr << "Failed to load font." << std::endl;
    }
    if (!scoreFont_.loadFromFile("../data/fonts/score_font.TTF")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    // --- Menu Banner ---
    menuBanner_.text.setFont(font_);
    menuBanner_.text.setFillColor(sf::Color::Black);
    menuBanner_.text.setString("Menu");
    menuBanner_.background.setFillColor(sf::Color::Yellow);
    menuBanner_.bg_height_multiplier = 1.5f;

    // --- Play Button ---
    playButton_.text.setFont(font_);
    playButton_.text.setFillColor(sf::Color::Black);
    playButton_.text.setString("Play");
    playButton_.background.setFillColor(sf::Color::White);
    playButton_.bg_height_multiplier = 1.2f;

    // --- High Scores Title ---
    highScoreTitle_.setFont(scoreFont_);
    highScoreTitle_.setFillColor(sf::Color::White);
    highScoreTitle_.setString("High Scores:");

    // --- High Scores List ---
    highScores_.reserve(5);

    int line_number = 0;
    for (auto& score : score_->get_high_scores()) {
        sf::Text file_score;
        file_score.setFont(scoreFont_);
        file_score.setFillColor(sf::Color::White);
        file_score.setString(std::to_string(line_number + 1) + ": " + score);
        highScores_.push_back(file_score);
        line_number++;
    }
    updateLayout(windowsize);
}

void representation::MenuState::centerButton(Button& button, const sf::Vector2u& windowSize, float y_pos_ratio) {
    float window_width = windowSize.x;
    float window_height = windowSize.y;
    unsigned int char_size = (window_width / 32 + window_height / 32);

    // Centreer tekst
    button.text.setCharacterSize(char_size);
    sf::FloatRect text_bounds = button.text.getLocalBounds();
    button.text.setOrigin(text_bounds.left + text_bounds.width / 2.0f, text_bounds.top + text_bounds.height / 2.0f);
    button.text.setPosition(window_width / 2.0f, window_height * y_pos_ratio);

    // Centreer achtergrond
    button.background.setSize({char_size * button.bg_width_multiplier, char_size * button.bg_height_multiplier});
    button.background.setOrigin(button.background.getSize() / 2.f);
    button.background.setPosition(window_width / 2.0f, window_height * y_pos_ratio);
}


void representation::MenuState::updateLayout(sf::Vector2u windowSize) {
    // --- Menu Banner (12.5% from top)---
    centerButton(menuBanner_, windowSize, 8.f / 64.f);

    // --- Play Button (90% from top) ---
    centerButton(playButton_, windowSize, 58.f / 64.f);

    // --- High Scores ---
    float window_width = windowSize.x;
    float window_height = windowSize.y;
    unsigned int char_size = (window_width / 64 + window_height / 64);

    // Titel
    highScoreTitle_.setCharacterSize(char_size);
    sf::FloatRect score_title_bounds = highScoreTitle_.getLocalBounds();
    highScoreTitle_.setOrigin(score_title_bounds.left + score_title_bounds.width / 2.0f, score_title_bounds.top + score_title_bounds.height / 2.0f);
    highScoreTitle_.setPosition(window_width / 2.f, window_height * (20.f/64.f));

    // Scores
    float current_y_ratio = 28.f / 64.f;
    for (auto& highScore : highScores_) {
        highScore.setCharacterSize(char_size * 0.9f);
        sf::FloatRect score_bounds = highScore.getLocalBounds();
        // DE FIX: gebruik 'highScore' in plaats van 'highScoreText_'
        highScore.setOrigin(score_bounds.left + score_bounds.width / 2.0f, score_bounds.top + score_bounds.height / 2.0f);
        highScore.setPosition(window_width / 2.f, window_height * current_y_ratio);
        current_y_ratio += (4.f / 64.f);
    }
}

void representation::MenuState::proces_user_input(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
        updateLayout({event.size.width, event.size.height});
        return; // Voorkom doorvallen naar MouseButtonPressed
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouseWorld = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        if (playButton_.background.getGlobalBounds().contains(mouseWorld)) {
            std::shared_ptr<Camera> cam = std::make_shared<Camera>();
            manager_.push_state(std::make_unique<LevelState>(manager_, window.getSize(), score_, cam));
        }
    }
}

void representation::MenuState::render(sf::RenderWindow& window) {
    window.draw(menuBanner_.background);
    window.draw(menuBanner_.text);

    window.draw(playButton_.background);
    window.draw(playButton_.text);

    window.draw(highScoreTitle_);
    for (const auto& highScore : highScores_) {
        window.draw(highScore);
    }
}