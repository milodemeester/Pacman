//
// Created by milod on 29/10/2025.
//
#include "../include/Game.h"
#include "../../Logic/include/Stopwatch.h"

Game::Game() {
    state_manager = new StateManager();
}


void Game::run() {
    Stopwatch* stopwatch = Stopwatch::create();
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Pacman", sf::Style::Default);
    int fps = 60;
    window.setFramerateLimit(fps);

    sf::View view = window.getDefaultView();

    while (window.isOpen()) {
        sf::Event event{};
        if (window.pollEvent(event)) {
            if (event.type == sf::Event::Resized) {
                view.setSize({static_cast<float>(event.size.width),static_cast<float>(event.size.height)});
                view.setCenter(event.size.width / 2.f, event.size.height / 2.f);
                window.setView(view);
            }
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