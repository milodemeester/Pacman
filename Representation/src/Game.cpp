//
// Created by milod on 29/10/2025.
//
#include "../include/Game.h"

#include "../../Logic/include/Score.h"
#include "../../Logic/include/Stopwatch.h"

representation::Game::Game() : window(sf::VideoMode({800, 600}), "Pacman", sf::Style::Default) ,
    state_manager(std::make_shared<StateManager>(window.getSize())) {}

void representation::Game::run() {
    logic::Stopwatch* stopwatch = logic::Stopwatch::create();
    logic::Score score;
    int fps = 60;
    window.setFramerateLimit(fps);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            state_manager->process_event(event, window);
        }
        state_manager->update(stopwatch->get_delta_time());
        window.clear(sf::Color::Black);
        state_manager->render(window);
        window.display();
    }
}