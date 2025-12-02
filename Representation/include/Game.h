//
// Created by milod on 29/10/2025.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include "StateManager.h"
#include <SFML/Graphics.hpp>

namespace representation {
class Game {
    std::shared_ptr<logic::Score> score_;
    sf::RenderWindow window_;
    std::shared_ptr<StateManager> state_manager_;

public:
    // constructor
    Game();

    /**
     * @brief runs the main game loop
     */
    void run();
};
} // namespace representation

#endif // PACMAN_GAME_H