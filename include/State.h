//
// Created by milod on 30/10/2025.
//

#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H
#include "SFML/Window/Event.hpp"
class StateFactory;

class State { // Abstract product
public:
    virtual ~State() = default;

    /*
     * Method to proces the input from the user
     */
    virtual std::pair<bool, State*> proces_user_input(const sf::Event::KeyPressed*, StateFactory*) = 0;
};

class LevelState final : public State{
public:
    std::pair<bool, State*> proces_user_input(const sf::Event::KeyPressed*, StateFactory*) override;
};

class PausedState final : public State{
public:
    std::pair<bool, State*> proces_user_input(const sf::Event::KeyPressed*, StateFactory*) override;
};

class VictoryState final : public State{
public:
    std::pair<bool, State*> proces_user_input(const sf::Event::KeyPressed*, StateFactory*) override;
};

class MenuState final : public State{
public:
    std::pair<bool, State*> proces_user_input(const sf::Event::KeyPressed*, StateFactory*) override;
};

class StateFactory{
public:
    LevelState* create_level_state();
    PausedState* create_paused_state();
    VictoryState* create_victory_state();
    MenuState* create_menu_state();
};


#endif //PACMAN_STATE_H

