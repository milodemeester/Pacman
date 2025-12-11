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

representation::MenuState::MenuState(StateManager& sm, sf::Vector2u windowsize, std::shared_ptr<logic::Score> score)
    : State(sm), score_(std::move(score)) {

    // font loading
    if (!font_.loadFromFile("../data/fonts/pacman_font.TTF")) {
        std::cerr << "Failed to load font in menustate." << std::endl;
        exit(1);
    }
    if (!scoreFont_.loadFromFile("../data/fonts/score_font.TTF")) {
        std::cerr << "Failed to load font in manustate." << std::endl;
        exit(1);
    }
    if (!texture_.loadFromFile("../data/textures/menu_state_img.png")) {
        std::cerr << "Failed to load texture in menustate." << std::endl;
        exit(1);
    }

    // --- High Scores Title ---
    highScoreTitle_.setFont(scoreFont_);
    highScoreTitle_.setFillColor(sf::Color::White);
    highScoreTitle_.setString("High Scores:");

    // --- High Scores List ---
    highScores_.reserve(5);

    int line_number = 0;
    for (auto& scoree : score_->get_high_scores()) {
        sf::Text file_score;
        file_score.setFont(scoreFont_);
        file_score.setFillColor(sf::Color::White);
        file_score.setString(std::to_string(line_number + 1) + ": " + scoree);
        highScores_.push_back(file_score);
        line_number++;
    }
    updateLayout(windowsize);
}

void representation::MenuState::updateLayout(sf::Vector2u windowSize) {
    // --- High Scores ---
    float window_width = windowSize.x;
    float window_height = windowSize.y;
    float char_size = (window_width / 64 + window_height / 64);

    // Titel
    highScoreTitle_.setCharacterSize(char_size);
    sf::FloatRect score_title_bounds = highScoreTitle_.getLocalBounds();
    highScoreTitle_.setOrigin(score_title_bounds.left + score_title_bounds.width / 2.0f,
                              score_title_bounds.top + score_title_bounds.height / 2.0f);
    highScoreTitle_.setPosition(window_width / 2.f, window_height * (22.f / 64.f));

    // Scores
    auto scores = score_->get_high_scores();
    float current_y_ratio = 28.f / 64.f;
    // update all the highScore-texts
    for (int i = 0; i < highScores_.size(); i++) {
        highScores_[i].setString(scores[i]);
        highScores_[i].setCharacterSize(char_size * 0.9f);
        sf::FloatRect score_bounds = highScores_[i].getLocalBounds();
        highScores_[i].setOrigin(score_bounds.left + score_bounds.width / 2.0f,
                                 score_bounds.top + score_bounds.height / 2.0f);
        highScores_[i].setPosition(window_width / 2.f, window_height * current_y_ratio);
        current_y_ratio += (4.f / 64.f);
    }
}

void representation::MenuState::proces_user_input(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
        updateLayout({event.size.width, event.size.height});
    }

    else if (event.type == sf::Event::MouseButtonPressed) {
        float x = event.mouseButton.x;
        float y = event.mouseButton.y;
        sf::Vector2f mouseCoords = {x, y};
        // check if the click is inside the button boundries
        Coordinate ulc = {button_.btnLeft_, button_.btnTop_};
        Coordinate lrc = {button_.btnRight_, button_.btnBottom_};
        Coordinate click = {mouseCoords.x, mouseCoords.y};
        if (utils::contains(ulc, lrc, click)) {
            std::shared_ptr<Camera> cam = std::make_shared<Camera>();
            manager_.push_state(std::make_unique<LevelState>(manager_, window.getSize(), score_, cam, 1));
        }
    }
}

void representation::MenuState::render(sf::RenderWindow& window) {
    // Load the image and resize it to fit the window
    sf::Sprite sprite;
    sprite.setTexture(texture_);
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
    auto winSize = window.getSize();
    auto local = sprite.getLocalBounds();

    float scaleX = winSize.x / local.width;
    float scaleY = winSize.y / local.height;

    float scale = std::min(scaleX, scaleY);

    sprite.setPosition(winSize.x / 2.f, winSize.y / 2.f);
    sprite.setScale(scale, scale);
    window.draw(sprite);

    float imgW = local.width;
    float imgH = local.height;

    auto size = window.getSize();

    float scaledW = imgW * scale;
    float scaledH = imgH * scale;

    float spriteLeft = (size.x - scaledW) / 2.f;
    float spriteTop = (size.y - scaledH) / 2.f;

    // save the boundires of the button (later used to calculate if a click falls into this)
    button_.btnLeft_ = spriteLeft + scaledW * 0.25f;
    button_.btnTop_ = spriteTop + scaledH * 0.86f;
    button_.btnRight_ = spriteLeft + scaledW * 0.75f;
    button_.btnBottom_ = spriteTop + scaledH * 0.97f;

    // draw to window
    window.draw(highScoreTitle_);
    for (const auto& highScore : highScores_) {
        window.draw(highScore);
    }
}

void representation::MenuState::update(float dt) {
    std::vector<std::string> scores = score_->get_high_scores();
    for (int i = 0; i < 5; i++) {
        highScores_[i].setString(scores[i]);
    }
}