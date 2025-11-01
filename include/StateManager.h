//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H
#include "SFML/Graphics/RenderWindow.hpp"
#include <stack>
class State;

class StateFactory;


class StateManager{
    std::stack<State*> state_stack;
    StateFactory* state_factory = nullptr;
public:
    StateManager();

    /*
     * Method to process a key-press event
     */
    void process_key_pressed(const sf::Event*);

    /*
     *
     */
    void render(sf::RenderWindow* window);
};


#endif //PACMAN_STATEMANAGER_H