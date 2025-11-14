//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "../../Logic/include/World.h"
#include "Camera.h"
#include "SpriteMap.h"
#include "State.h"

namespace logic {
class Score;
}
namespace representation {
class StateManager;
class SfmlFactory;
class EntityView;
}

namespace representation {
class LevelState final : public representation::State {
    void updateLayout(sf::Vector2u windowSize);
    std::shared_ptr<logic::Score> score_;
    std::shared_ptr<representation::Camera> camera_;
    SpriteMap spriteMap_;
    std::shared_ptr<representation::SfmlFactory> factory_;
    logic::World world_;
    std::vector<std::unique_ptr<representation::EntityView>> views_;

    sf::Font scoreFont_;
    sf::Text scoreTitle_;

public:

    LevelState(StateManager& manager, sf::Vector2u windowSize, std::shared_ptr<logic::Score> score, std::shared_ptr<Camera> camera);
    void proces_user_input(const sf::Event& event, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
    void update(double delta_time) override;
};
} // namespace representation

#endif // PACMAN_LEVELSTATE_H