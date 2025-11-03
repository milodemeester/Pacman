//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "State.h"
class World;

class LevelState final : public State{
    World* world;
public:
    LevelState();
    std::pair<bool, State*> proces_user_input(const sf::Event*) override;
    void render(sf::RenderWindow*) override;
    void update(double delta_time) override;
};

#endif // PACMAN_LEVELSTATE_H
