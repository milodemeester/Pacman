//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <stack>

namespace sf {
class Event;
class RenderWindow;
}
namespace representation {
class State;

class StateManager {
    std::stack<std::unique_ptr<State>> state_stack;
    sf::Vector2u currentWindowSize;

public:
    explicit StateManager(sf::Vector2u windowSize);
    /*
     * Method to process a key-press event
     */
    void process_event(const sf::Event&, sf::RenderWindow& window);

    /*
     * Method that pops the top of the state_stack
     */
    bool pop_state();

    /*
     * Pushes a state onto the stack
     */
    void push_state(std::unique_ptr<State> state);

    /*
     * Function that draws everyting on the window
     */
    void render(sf::RenderWindow& window);

    /*
     * Method that is used to update the game
     */
    void update(double delta_time);
};
} // namespace representation

#endif // PACMAN_STATEMANAGER_H