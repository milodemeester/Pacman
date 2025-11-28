//
// Created by milo on 11/1/25.
//

#include "../include/LevelState.h"

#include "../../Logic/include/Score.h"
#include "../include/EntityView.h"
#include "../include/GhostView.h"
#include "../include/PacmanView.h"
#include "../include/PausedState.h"
#include "../include/SfmlFactory.h"
#include "../include/SpriteMap.h"
#include "../include/StateManager.h"
#include "../include/VictoryState.h"

#include <SFML/Window/Event.hpp>

#include <iostream>
#include <utility>

representation::LevelState::LevelState(StateManager& manager, sf::Vector2u windowSize,
                                       std::shared_ptr<logic::Score> score, std::shared_ptr<Camera> camera, int level = 1)
    : State(manager), score_(std::move(score)), camera_(std::move(camera)), spriteMap_("../data/sprite.png"),
      factory_(std::make_shared<SfmlFactory>(camera_, windowSize, spriteMap_, score_)), world_(factory_, level), manager_(manager) {

    // Font inladen
    if (!font_.loadFromFile("../data/fonts/score_font.TTF")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    windowSize_ = windowSize;
    scoreTitle_.setFont(font_);
    scoreTitle_.setFillColor(sf::Color::Yellow);
    scoreTitle_.setString("Score: " + std::to_string(score_->get_score()));

    livesTitle_.setFont(font_);
    livesTitle_.setFillColor(sf::Color::Yellow);
    livesTitle_.setString("#Lives: " + std::to_string(world_.get_pacman_lives()));

    levelTitle_.setFont(font_);
    levelTitle_.setFillColor(sf::Color::Yellow);
    livesTitle_.setString("Level: " + std::to_string((world_.get_level())));


    // Camera initialiseren
    camera_->updateScreenSize(windowSize, {float(world_.get_width()), float(world_.get_height())});
    updateLayout(windowSize);

    views_ = factory_->getCreatedViews();
}

void representation::LevelState::proces_user_input(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Resized) {
        windowSize_ = sf::Vector2u(event.size.width, event.size.height);
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));

        // Update de camera met de nieuwe grootte
        sf::Vector2u newSize(event.size.width, event.size.height);
        camera_->updateScreenSize(newSize, {float(world_.get_width()), float(world_.get_height())});

        // Update de UI layout
        updateLayout(newSize);
    } else if (event.type == sf::Event::KeyPressed) {
        auto key = event.key.code;
        if (key == sf::Keyboard::Up) {
            world_.move_pacman(logic::Direction::North);
        } else if (key == sf::Keyboard::Down) {
            world_.move_pacman(logic::Direction::South);
        } else if (key == sf::Keyboard::Right) {
            world_.move_pacman(logic::Direction::East);
        } else if (key == sf::Keyboard::Left) {
            world_.move_pacman(logic::Direction::West);
        } else if (key == sf::Keyboard::Escape) {
            std::unique_ptr<PausedState> paused = std::make_unique<PausedState>(manager_, window.getSize());
            manager_.push_state(std::move(paused));
        }
    }
}

void representation::LevelState::update(double delta_time) {
    world_.update(delta_time);
    for (const auto& view : views_) {
        view->update(delta_time);
    }
    logic::WorldState world_state = world_.get_world_state();
    switch (world_state) {
    case (logic::WorldState::Running):  {
        return;
    }
    case (logic::WorldState::Defeated): {
        score_->update_high_scores();
        score_->reset();
        manager_.pop_state();
        }
    case (logic::WorldState::Victory): {
        auto level_state = std::make_unique<LevelState>(manager_, windowSize_, score_, camera_, world_.get_level()+1);
        manager_.pop_state();
        manager_.push_state(std::move(level_state));
        auto victory_state = std::make_unique<VictoryState>(manager_);
        manager_.push_state(std::move(victory_state));
    }
    }
}

void representation::LevelState::render(sf::RenderWindow& window) {
    std::shared_ptr<PacmanView> pacman;
    std::vector<std::shared_ptr<GhostView>> ghosts;

    for (auto& view : views_) {
        if (std::dynamic_pointer_cast<PacmanView>(view)) {
            pacman = std::dynamic_pointer_cast<PacmanView>(view);
        } else if (dynamic_pointer_cast<GhostView>(view)) {
            ghosts.push_back(std::dynamic_pointer_cast<GhostView>(view));
        } else {
            view->draw(window, camera_);
        }
    }
    for (auto& ghost : ghosts) {
        ghost->draw(window, camera_);
    }
    if (pacman) {
        pacman->draw(window, camera_);
    }

    updateLayout(window.getSize());
    window.draw(scoreTitle_);
    window.draw(livesTitle_);
    window.draw(levelTitle_);
}

void representation::LevelState::updateLayout(sf::Vector2u windowSize) {
    float window_width = static_cast<float>(windowSize.x);
    float window_height = static_cast<float>(windowSize.y);

    // Opgeslagen pos van onderkant speelbord in cameraa
    float board_bottom = camera_->getBoardBottomY();

    // Hoogte die is "gereserveerd" voor de UI onder het bord
    float ui_bar_height = std::max(0.f, window_height - board_bottom);

    // Bereken character size op basis van UI-balk hoogte
    unsigned int char_size = static_cast<unsigned int>(std::max(12.f, ui_bar_height * 0.45f));
    unsigned int char_size_max = static_cast<unsigned int>(std::max(24.f, (window_width + window_height) / 40.f));
    if (char_size > char_size_max) {
        char_size = char_size_max;
    }

    // ----- score -----
    // Update de score tekst en grootte
    scoreTitle_.setCharacterSize(camera_->getBlockSize());
    scoreTitle_.setString("Score: " + std::to_string(score_->get_score()));

    sf::FloatRect bounds = scoreTitle_.getLocalBounds();
    scoreTitle_.setOrigin(bounds.left, bounds.top + bounds.height / 2.f);

    // Horizontaal gecentreerd in het venster; verticaal: midden van UI-balk onder het bord
    scoreTitle_.setPosition(camera_->getBoardLeftX(), board_bottom + ui_bar_height / 2.f);

    // ----- lives -----
    // Update de lives tekst en grootte
    livesTitle_.setCharacterSize(camera_->getBlockSize());
    livesTitle_.setString("#Lives: " + std::to_string(world_.get_pacman_lives()));

    bounds = livesTitle_.getLocalBounds();
    livesTitle_.setOrigin(bounds.left + bounds.width, bounds.top + bounds.height / 2.f);

    // Horizontaal gecentreerd in het venster; verticaal: midden van UI-balk onder het bord
    livesTitle_.setPosition(camera_->getBoardLeftX() + camera_->getBlockSize()*world_.get_width(), board_bottom + ui_bar_height / 2.f);

    // ----- level -----
    // Update de lives tekst en grootte
    levelTitle_.setCharacterSize(camera_->getBlockSize());
    levelTitle_.setString("Level: " + std::to_string(world_.get_level()));

    bounds = levelTitle_.getLocalBounds();
    levelTitle_.setOrigin((bounds.left + bounds.width)/ 2.f, bounds.top + bounds.height / 2.f);

    // Horizontaal gecentreerd in het venster; verticaal: midden van UI-balk onder het bord
    levelTitle_.setPosition((camera_->getBoardLeftX() + (camera_->getBoardLeftX() + camera_->getBlockSize()*world_.get_width()))/2.f, board_bottom + ui_bar_height / 2.f);
}