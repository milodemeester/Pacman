//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_VICTORYSTATE_H
#define PACMAN_VICTORYSTATE_H
#include "State.h"
#include <SFML/Graphics/Texture.hpp>

namespace representation {
namespace state {
class VictoryState final : public State {
    sf::Texture texture_;
    Button button_;

public:
    // constructor
    explicit VictoryState(StateManager& sm);

    /**
     * @brief processes the input of the user
     * @param event the event that needs to be processed
     * @param window the window where the changes will have to be written to
     */
    void proces_user_input(const sf::Event& event, sf::RenderWindow& window) override;

    /**
     * @brief render everything
     * @param window the window that needs to be written to
     */
    void render(sf::RenderWindow& window) override;
};
}
} // namespace representation

#endif // PACMAN_VICTORYSTATE_H
