//
// Created by milod on 29/10/2025.
//
#include "../include/Game.h"

#include "../../Logic/include/Score.h"
#include "../../Logic/include/Stopwatch.h"

representation::Game::Game()
    : score_(nullptr), window_(sf::VideoMode({1600, 800}), "Pacman", sf::Style::Default), state_manager_(nullptr) {}

void representation::Game::run() {
    std::shared_ptr<logic::Score> s = std::make_shared<logic::Score>();
    score_ = s;
    state_manager_ = std::make_shared<StateManager>(window_.getSize(), score_);
    std::shared_ptr<logic::Stopwatch> stopwatch = logic::Stopwatch::getInstance();
    int fps = 60;
    window_.setFramerateLimit(fps);

    while (window_.isOpen()) {
        sf::Event event{};
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_.close();
            }
            state_manager_->process_event(event, window_);
        }
        state_manager_->update(stopwatch->get_delta_time());
        window_.clear(sf::Color::Black);
        state_manager_->render(window_);
        window_.display();
    }
}