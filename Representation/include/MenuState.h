//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H
#include "../../Logic/include/Score.h"
#include "State.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory>

namespace logic {
class Score;
}
namespace representation {
class MenuState final : public State {
    /**
     * @brief update all the texts, buttons and high scores
     * @param windowSize size of the window
     */
    void updateLayout(sf::Vector2u windowSize);

    std::shared_ptr<logic::Score> score_;
    sf::Font font_;
    sf::Font scoreFont_;

    sf::Text highScoreTitle_;
    std::vector<sf::Text> highScores_;

    Button button_;
    sf::Texture texture_;

public:
    // constructor
    explicit MenuState(StateManager& sm, sf::Vector2u windowsize, std::shared_ptr<logic::Score> score);

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

    /**
     * @brief update every entity and check if there is a victory or defeat
     * @param dt time between this and the previous update
     */
    void update(float dt) override;
};
} // namespace representation

#endif // PACMAN_MENUSTATE_H
