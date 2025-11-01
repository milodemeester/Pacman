//
// Created by milo on 11/1/25.
//

#ifndef PACMAN_STATEFACTORY_H
#define PACMAN_STATEFACTORY_H

class LevelState;
class PausedState;
class MenuState;
class VictoryState;

class StateFactory{
public:
    LevelState* create_level_state();
    PausedState* create_paused_state();
    VictoryState* create_victory_state();
    MenuState* create_menu_state();
};

#endif // PACMAN_STATEFACTORY_H
