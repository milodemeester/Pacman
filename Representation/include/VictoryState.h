//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_VICTORYSTATE_H
#define PACMAN_VICTORYSTATE_H
#include "LevelState.h"
#include "State.h"

#include <memory>

class VictoryState final : public State{
public:
    std::pair<int, std::unique_ptr<State>> proces_user_input(const sf::Event& event, sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

};

#endif // PACMAN_VICTORYSTATE_H
