//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_PAUSEDSTATE_H
#define PACMAN_PAUSEDSTATE_H
#include "State.h"
#include <SFML/Graphics/Texture.hpp>

namespace representation {
namespace state {
class PausedState final : public State {
    /**
     * @brief update all the text
     * @param windowSize size of the window
     */
    void updateLayout(sf::Vector2u windowSize);
    sf::Texture texture_;

    Button button1_;
    Button button2_;

public:
    // constructor
    PausedState(StateManager& sm, sf::Vector2u windowsize);

    /**
     * @brief processes the input of the user
     * @param event the event that needs to be processed
     * @param window the window where the changes will have to be written to
     */
    void proces_user_input(const sf::Event&, sf::RenderWindow& window) override;

    /**
     * @brief render everything
     * @param window the window that needs to be written to
     */
    void render(sf::RenderWindow& window) override;
};
}
} // namespace representation
#endif // PACMAN_PAUSEDSTATE_H
