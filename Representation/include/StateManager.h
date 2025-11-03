//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H
#include "../../Logic/include/Score.h"
#include "SFML/Graphics/RenderWindow.hpp"

#include <memory>
#include <stack>
class State;

class StateManager{
    std::stack<std::unique_ptr<State>> state_stack;
    Score* score;
public:
    StateManager();

    /*
     * Method to process a key-press event
     */
    void process_event(const sf::Event&, sf::RenderWindow& window);

    /*
     * Function that draws everyting on the window
     */
    void render(sf::RenderWindow& window);

    /*
     * Method that is used to update the game
     */
    void update(double delta_time);
};


#endif //PACMAN_STATEMANAGER_H