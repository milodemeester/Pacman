//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Window.hpp"
#include "StateManager.h"
#include <memory>
#include <utility>

class Score;
class StateManager;
class StateFactory;

namespace representation {
class State { // Abstract product
protected:
    StateManager manager_;

public:
    State(StateManager& manager) : manager_(manager) {}
    virtual ~State() = default;

    /*
     * Method to proces the input from the user
     */
    virtual void proces_user_input(const sf::Event&, sf::RenderWindow& window) = 0;

    /*
     * Method that takes care of drawing on the window in the current state
     */
    virtual void render(sf::RenderWindow& window) = 0;

    virtual void update(double delta_time);
};
} // namespace representation

#endif // PACMAN_STATE_H
