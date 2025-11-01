//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Window.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

#include <utility>

class StateFactory;

class State { // Abstract product
public:
    virtual ~State() = default;

    /*
     * Method to proces the input from the user
     */
    virtual std::pair<bool, State*> proces_user_input(const sf::Event*, StateFactory*) = 0;


    /*
     * Method that takes care of drawing on the window in the current state
     */
    virtual void render(sf::RenderWindow*) = 0;
};


#endif //PACMAN_STATE_H

