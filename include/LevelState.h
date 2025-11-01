//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_LEVELSTATE_H
#define PACMAN_LEVELSTATE_H
#include "State.h"
#include "StateFactory.h"
#include "World.h"

class LevelState final : public State{
    World world;
public:
    std::pair<bool, State*> proces_user_input(const sf::Event*, StateFactory*) override;
    void render(sf::RenderWindow*) override;
};

#endif // PACMAN_LEVELSTATE_H
