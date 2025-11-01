//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_VICTORYSTATE_H
#define PACMAN_VICTORYSTATE_H
#include "StateFactory.h"
#include "State.h"

class VictoryState final : public State{
public:
    std::pair<bool, State*> proces_user_input(const sf::Event*, StateFactory*) override;
    void render(sf::RenderWindow*) override;

};

#endif // PACMAN_VICTORYSTATE_H
