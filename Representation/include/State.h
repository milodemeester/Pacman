//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace representation {
struct Button {
    sf::Text text;
    sf::RectangleShape background;
    float bg_width_multiplier = 5.f; // Multiplier voor achtergrondbreedte
    float bg_height_multiplier = 1.3f; // Multiplier voor achtergrondhoogte
};

class Camera;
class StateManager;
class State { // Abstract product
protected:
    StateManager& manager_;
public:
    explicit State(StateManager& manager) : manager_(manager) {}
    virtual ~State() = default;

    /*
     * Method to proces the input from the user
     */
    virtual void proces_user_input(const sf::Event&, sf::RenderWindow& window) = 0;

    /*
     * Method that takes care of drawing on the window in the current state (without cam for every other state)
     */
    virtual void render(sf::RenderWindow& window) = 0;

    virtual void update(double delta_time);
};
} // namespace representation

#endif // PACMAN_STATE_H
