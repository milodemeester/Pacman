//
// Created by milod on 29/10/2025.
//
#include "../include/Game.h"

#include "../../Logic/include/Score.h"
#include "../../Logic/include/Stopwatch.h"

representation::Game::Game()
    : score_(nullptr), window_(sf::VideoMode({1600, 800}), "Pacman", sf::Style::Default), state_manager_(nullptr) {}

void representation::Game::run() {
    // initialisation
    std::shared_ptr<logic::core::Score> s = std::make_shared<logic::core::Score>();
    score_ = s;
    state_manager_ = std::make_shared<state::StateManager>(window_.getSize(), s);
    std::shared_ptr<logic::core::Stopwatch> stopwatch = logic::core::Stopwatch::getInstance();
    window_.setVerticalSyncEnabled(true);

    // main game loop
    while (window_.isOpen()) {
        sf::Event event{};
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_.close();
            }
            state_manager_->process_event(event, window_);
        }
        //state_manager_->update(20); // for debugging
        state_manager_->update(stopwatch->get_delta_time());
        window_.clear(sf::Color::Black);
        state_manager_->render(window_);
        window_.display();
    }
}