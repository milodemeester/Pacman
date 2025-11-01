//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H
#include "SFML/Graphics/RenderWindow.hpp"
#include "Score.h"
#include <stack>
class State;

class StateFactory;


class StateManager{
    std::stack<State*> state_stack;
    StateFactory* state_factory = nullptr;
    Score score;
public:
    StateManager();

    /*
     * Method to process a key-press event
     */
    void process_key_pressed(const sf::Event*);

    /*
     * Function that draws everyting on the window
     */
    void render(sf::RenderWindow* window);

    /*
     * Method that is used to update the game
     */
    void update(double delta_time);
};


#endif //PACMAN_STATEMANAGER_H