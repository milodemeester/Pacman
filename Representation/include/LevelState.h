//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "../../Logic/include/World.h"
#include "Camera.h"
#include "SpriteMap.h"
#include "State.h"

namespace representation {
class StateManager;
class SfmlFactory;

class EntityView;
}

namespace representation {
class LevelState final : public representation::State {
    representation::Camera camera;
    SpriteMap spriteMap_;
    std::shared_ptr<representation::SfmlFactory> factory;
    logic::World world;
    std::vector<std::unique_ptr<representation::EntityView>> views;
public:
    LevelState(StateManager& manager, sf::Vector2u windowSize);
    void proces_user_input(const sf::Event& event, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window, Camera& camera) override;
    void render(sf::RenderWindow& window) override;
    void update(double delta_time) override;
};
} // namespace representation

#endif // PACMAN_LEVELSTATE_H