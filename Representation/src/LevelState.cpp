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
#include <SFML/Window/Event.hpp>

#include <iostream>

representation::LevelState::LevelState(StateManager& manager, sf::Vector2u windowSize, std::shared_ptr<logic::Score> score, std::shared_ptr<Camera> camera)
    : camera_(camera),
    State(manager),
    spriteMap_("../data/sprite.png"),
    factory_(std::make_shared<SfmlFactory>(camera_, windowSize, spriteMap_)),
    world_(factory_),
    score_(score)
{
    camera_->updateScreenSize(windowSize, {float(world_.get_width()), float(world_.get_height())});

    updateLayout(windowSize);

    views_ = factory_->getCreatedViews();

    if (!scoreFont_.loadFromFile("../data/fonts/score_font.TTF")) {
        std::cerr << "Failed to load font." << std::endl;
    }

    // --- Score text ---
    scoreTitle_.setFont(scoreFont_);
    scoreTitle_.setFillColor(sf::Color::White);
    scoreTitle_.setString("Score: 0");
}

void representation::LevelState::proces_user_input(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));

        // Update de camera met de nieuwe grootte
        sf::Vector2u newSize(event.size.width, event.size.height);
        camera_->updateScreenSize(newSize, {float(world_.get_width()), float(world_.get_height())});

        // Update de UI layout
        updateLayout(newSize);
    }
    else if (event.type == sf::Event::KeyPressed) {
        auto key = event.key.code;
        if (key == sf::Keyboard::Up) {
            world_.move_pacman(logic::Direction::North);
        }
        else if (key == sf::Keyboard::Down)  {
            world_.move_pacman(logic::Direction::South);
        }
        else if (key == sf::Keyboard::Right) {
            world_.move_pacman(logic::Direction::East);
        }
        else if (key == sf::Keyboard::Left) {
            world_.move_pacman(logic::Direction::West);
        }
        else if (key == sf::Keyboard::Escape) {
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
}

void representation::LevelState::render(sf::RenderWindow& window) {
    std::shared_ptr<PacmanView> pacman;
    std::vector<std::shared_ptr<GhostView>> ghosts;

    for (auto& view : views_) {
        if (std::dynamic_pointer_cast<PacmanView>(view)) {
            pacman = std::dynamic_pointer_cast<PacmanView>(view);
        }
        else if (dynamic_pointer_cast<GhostView>(view)) {
            ghosts.push_back(std::dynamic_pointer_cast<GhostView>(view));
        }
        else {
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
}

void representation::LevelState::updateLayout(sf::Vector2u windowSize) {
    float window_width = windowSize.x;
    float window_height = windowSize.y;

    // Haal de positie van de onderkant van het bord direct uit de camera
    float board_bottom = camera_->getBoardBottomY();

    // Bepaal het midden van de UI-balk die eronder zit
    float ui_bar_center_y = board_bottom + (window_height - board_bottom) / 2.0f;
    unsigned int char_size = (window_height - board_bottom) * 0.4f;

    // Update de score tekst
    std::string score = "Score: " + std::to_string(score_->get_score());
    scoreTitle_.setString(score);
    scoreTitle_.setCharacterSize(char_size);

    // Centreer en positioneer de tekst
    sf::FloatRect bounds = scoreTitle_.getLocalBounds();
    //scoreTitle_.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    scoreTitle_.setPosition(window_width / 4.f, ui_bar_center_y);
}