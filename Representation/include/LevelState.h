//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "../../Logic/include/World.h"
#include "Camera.h"
#include "State.h"

class LevelState final : public State {
    Camera camera;
    World world;

public:
    LevelState(sf::RenderWindow& window);
    std::pair<int, std::unique_ptr<State>> proces_user_input(const sf::Event& event, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;
    void update(double delta_time) override;
};

#endif // PACMAN_LEVELSTATE_H