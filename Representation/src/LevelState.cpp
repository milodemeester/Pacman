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
                                       std::shared_ptr<logic::Score> score, std::shared_ptr<Camera> camera,
                                       int level = 1, int pacman_lives)
    : State(manager), score_(std::move(score)), camera_(std::move(camera)), spriteMap_("../data/sprite.png"),
      factory_(std::make_shared<SfmlFactory>(camera_, windowSize, spriteMap_, score_)),
      world_(factory_, level, pacman_lives), manager_(manager) {

    // Load font
    if (!font_.loadFromFile("../data/fonts/score_font.TTF")) {
        std::cerr << "Failed to load font in levelstate" << std::endl;
        exit(1);
    }

    // initialize all the text
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

    // initialize camera
    camera_->updateScreenSize(windowSize, {float(world_.get_width()), float(world_.get_height())});
    updateLayout(windowSize);

    views_ = factory_->getCreatedViews();
}

void representation::LevelState::proces_user_input(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Resized) {
        // update view
        windowSize_ = sf::Vector2u(event.size.width, event.size.height);
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));

        // update the camera with the new size
        sf::Vector2u newSize(event.size.width, event.size.height);
        camera_->updateScreenSize(newSize, {float(world_.get_width()), float(world_.get_height())});

        // update text
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
    // check if this level has ended
    logic::WorldState world_state = world_.get_world_state();
    switch (world_state) {
    case (logic::WorldState::Running): {
        return;
    }
    case (logic::WorldState::Defeated): {
        // defeat, back to menu
        score_->update_high_scores();
        score_->reset();
        manager_.pop_state();
        return;
    }
    case (logic::WorldState::Victory): {
        // victory, pop this level, push new level and victory state
        auto level_state = std::make_unique<LevelState>(manager_, windowSize_, score_, camera_, world_.get_level() + 1,
                                                        world_.get_pacman_lives());
        manager_.pop_state();
        manager_.push_state(std::move(level_state));
        auto victory_state = std::make_unique<VictoryState>(manager_);
        manager_.push_state(std::move(victory_state));
        return;
    }
    }
}

void representation::LevelState::render(sf::RenderWindow& window) {
    std::shared_ptr<PacmanView> pacman;
    std::vector<std::shared_ptr<GhostView>> ghosts;

    // render every view (except pacman and ghosts)
    for (auto& view : views_) {
        if (std::dynamic_pointer_cast<PacmanView>(view)) {
            pacman = std::dynamic_pointer_cast<PacmanView>(view);
        } else if (dynamic_pointer_cast<GhostView>(view)) {
            ghosts.push_back(std::dynamic_pointer_cast<GhostView>(view));
        } else {
            view->draw(window, camera_);
        }
    }
    // then pacman and ghosts (so they will be on top, and not the other way around)
    for (auto& ghost : ghosts) {
        ghost->draw(window, camera_);
    }
    if (pacman) {
        pacman->draw(window, camera_);
    }

    // text
    scoreTitle_.setString("Score: " + std::to_string(score_->get_score()));
    livesTitle_.setString("#Lives: " + std::to_string(world_.get_pacman_lives()));
    window.draw(scoreTitle_);
    window.draw(livesTitle_);
    window.draw(levelTitle_);
}

void representation::LevelState::updateLayout(sf::Vector2u windowSize) {
    float window_width = static_cast<float>(windowSize.x);
    float window_height = static_cast<float>(windowSize.y);

    float board_bottom = camera_->getBoardBottomY();

    // this height was reserved in the camera for all the text
    float ui_bar_height = std::max(0.f, window_height - board_bottom);

    // calculate char size based on the height of the reserved space
    unsigned int char_size = static_cast<unsigned int>(std::max(12.f, ui_bar_height * 0.45f));
    unsigned int char_size_max = static_cast<unsigned int>(std::max(24.f, (window_width + window_height) / 40.f));
    if (char_size > char_size_max) {
        char_size = char_size_max;
    }

    // ----- score -----
    // Update score text en size
    scoreTitle_.setCharacterSize(camera_->getBlockSize());
    scoreTitle_.setString("Score: " + std::to_string(score_->get_score()));

    sf::FloatRect bounds = scoreTitle_.getLocalBounds();
    scoreTitle_.setOrigin(bounds.left, bounds.top + bounds.height / 2.f);

    // left side of the game board
    scoreTitle_.setPosition(camera_->getBoardLeftX(), board_bottom + ui_bar_height / 2.f);

    // ----- lives -----
    // Update lives text en size
    livesTitle_.setCharacterSize(camera_->getBlockSize());
    livesTitle_.setString("#Lives: " + std::to_string(world_.get_pacman_lives()));

    bounds = livesTitle_.getLocalBounds();
    livesTitle_.setOrigin(bounds.left + bounds.width, bounds.top + bounds.height / 2.f);

    // on the right side of the game board
    livesTitle_.setPosition(camera_->getBoardLeftX() + camera_->getBlockSize() * world_.get_width(),
                            board_bottom + ui_bar_height / 2.f);

    // ----- level -----
    // Update lives text en size
    levelTitle_.setCharacterSize(camera_->getBlockSize());
    levelTitle_.setString("Level: " + std::to_string(world_.get_level()));

    bounds = levelTitle_.getLocalBounds();
    levelTitle_.setOrigin((bounds.left + bounds.width) / 2.f, bounds.top + bounds.height / 2.f);

    // in the middle of the game board
    levelTitle_.setPosition(
        (camera_->getBoardLeftX() + (camera_->getBoardLeftX() + camera_->getBlockSize() * world_.get_width())) / 2.f,
        board_bottom + ui_bar_height / 2.f);
}