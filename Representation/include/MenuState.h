//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_MENUSTATE_H
#define PACMAN_MENUSTATE_H
#include "State.h"

class MenuState final : public State{
public:
    std::pair<bool, State*> proces_user_input(const sf::Event*) override;
    void render(sf::RenderWindow*) override;

};
#endif // PACMAN_MENUSTATE_H
