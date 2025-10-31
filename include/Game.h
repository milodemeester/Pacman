//
// Created by milod on 29/10/2025.
//

#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H
#include "StateManager.h"
#include "Stopwatch.h"
#include <SFML/Graphics.hpp>


class Game{
    sf::RenderWindow window;
    Stopwatch* stopwatch;
    StateManager* state_manager;
public:
    Game();

    /*
     * main game loop
     */
    void run();

};


#endif //PACMAN_GAME_H