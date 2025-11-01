//
// Created by milod on 29/10/2025.
//

#include "../include/Game.h"

Game::Game() {
    state_manager = new StateManager();
}


void Game::run() {
    window = new sf::RenderWindow(sf::VideoMode({800, 600}), "Pacman", sf::Style::Default);
    window->setFramerateLimit(60);
    window->setMouseCursorVisible(false);

    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Resized>()) {
                auto resized = event->getIf<sf::Event::Resized>();
                auto size = resized->size;
                float size_x = size.x;
                float size_y = size.y;
                sf::FloatRect visibleArea({0, 0}, {size_x, size_y});
                window->setView(sf::View(visibleArea));
            }
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
            state_manager->process_key_pressed(&event.value());
        }
        window->clear(sf::Color::Black);
        state_manager->render(window);
        window->display();
    }
}