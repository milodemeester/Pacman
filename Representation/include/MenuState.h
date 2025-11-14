//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H
#include <SFML/Graphics/RectangleShape.hpp>
#include "State.h"
#include "../../Logic/include/Score.h"
#include <SFML/Graphics/Text.hpp>
#include <memory>

namespace logic {
class Score;
}
namespace representation {
class MenuState final : public State {
    void updateLayout(sf::Vector2u windowSize);
    // Hulpfunctie om een knop te centreren
    static void centerButton(Button& button, const sf::Vector2u& windowSize, float y_pos_ratio);

    std::shared_ptr<logic::Score> score_;
    sf::Font font_;
    sf::Font scoreFont_;

    Button menuBanner_;
    Button playButton_;

    sf::Text highScoreTitle_;
    std::vector<sf::Text> highScores_;
public:
    explicit MenuState(StateManager& sm,  sf::Vector2u windowsize, std::shared_ptr<logic::Score> score);
    void proces_user_input(const sf::Event& event, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
};
} // namespace representation

#endif // PACMAN_MENUSTATE_H
