//
// Created by milod on 29/10/2025.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include "StateManager.h"
#include <SFML/Graphics.hpp>

namespace representation {
class Game {
    sf::RenderWindow window;
    std::shared_ptr<StateManager> state_manager;

public:
    Game();

    /*
     * main game loop
     */
    void run();
};
} // namespace representation

#endif // PACMAN_GAME_H