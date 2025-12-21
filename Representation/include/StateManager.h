//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_STATEMANAGER_H
#define PACMAN_STATEMANAGER_H
#include "State.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>

namespace logic::core {
class Score;
}
namespace sf {
class RenderWindow;
class Event;
} // namespace sf

namespace representation {
namespace state {
class State;

class StateManager {
    std::stack<std::unique_ptr<State>> state_stack;
    sf::Vector2u currentWindowSize;

public:
    // StateManager(const StateManager&) = delete;
    StateManager& operator=(const StateManager&) = delete;

    explicit StateManager(sf::Vector2u windowSize, const std::shared_ptr<logic::core::Score>& score);
    /**
     * Method to process a key-press event
     */
    void process_event(const sf::Event&, sf::RenderWindow& window);

    /**
     * Method that pops the top of the state_stack
     */
    bool pop_state();

    /**
     * Used for popping 2 states, instead of 1 (only used when going from paused state back to manu)
     */
    bool double_pop_state();

    /**
     * Pushes a state onto the stack
     */
    void push_state(std::unique_ptr<State> state);

    /**
     * Function that draws everyting on the window
     */
    void render(sf::RenderWindow& window);

    /**
     * Method that is used to update the game
     */
    void update(float delta_time);
};
} // namespace state
} // namespace representation

#endif // PACMAN_STATEMANAGER_H