//
// Created by milod on 29/10/2025.
//

#include "Game.h"

Game::Game() {
    Stopwatch* watch = new Stopwatch();
    state_manager = new StateManager();
}


void Game::run() {
    window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Pacman",
                                sf::Style::Default);
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::KeyPressed>()) {
                state_manager->process_key_pressed(event->getIf<sf::Event::KeyPressed>());
            }
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
