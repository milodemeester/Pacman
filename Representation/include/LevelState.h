//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "Camera.h"
#include "State.h"
#include "../../Logic/include/World.h"



namespace representation {
class StateManager;
class SfmlFactory;

class EntityView;
}

namespace representation {
class LevelState final : public representation::State {
    representation::Camera camera;
    std::shared_ptr<representation::SfmlFactory> factory;
    logic::World world;
    std::vector<std::unique_ptr<representation::EntityView>> views;

public:
    LevelState(StateManager& manager, sf::Vector2u windowSize);
    void proces_user_input(const sf::Event& event, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
    void update(double delta_time) override;
};
} // namespace representation

#endif // PACMAN_LEVELSTATE_H