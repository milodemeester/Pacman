//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "../../Logic/include/World.h"
#include "Camera.h"
#include "SpriteMap.h"
#include "State.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

namespace logic {
class Score;
}
namespace representation {
class StateManager;
class SfmlFactory;
class EntityView;

class LevelState final : public State {
    /**
     * @brief update all the texts, buttons and scores
     * @param windowSize size of the window
     */
    void updateLayout(sf::Vector2u windowSize);
    std::shared_ptr<logic::Score> score_;  // the score that was created outside of LevelState
    std::shared_ptr<Camera> camera_;       // the camera that is used to convert to pixel-ccordinates
    SpriteMap spriteMap_;                  // the spritemap that is used to get the sprites for different entities
    std::shared_ptr<SfmlFactory> factory_; // factory that is used to create all the entities
    logic::World world_;                   // the world that is created every level
    std::vector<std::shared_ptr<EntityView>> views_; // vector with every view
    StateManager& manager_;
    sf::Vector2u windowSize_;
    sf::Font font_; // font that is used for all the text in levelstate
    sf::Text scoreTitle_;
    sf::Text livesTitle_;
    sf::Text levelTitle_;

public:
    // constructor
    LevelState(StateManager& manager, sf::Vector2u windowSize, std::shared_ptr<logic::Score> score,
               std::shared_ptr<Camera> camera, int level, int pacman_lives = 3);

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
     * @param delta_time time between this and the previous update
     */
    void update(double delta_time) override;
};
} // namespace representation

#endif // PACMAN_LEVELSTATE_H