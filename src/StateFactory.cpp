//
// Created by milo on 11/1/25.
//

#include "../include/StateFactory.h"
#include "../include/MenuState.h"
#include "../include/VictoryState.h"
#include "../include/LevelState.h"
#include "../include/PausedState.h"

MenuState* StateFactory::create_menu_state() {
    auto* m = new MenuState{};
    return m;
}
LevelState* StateFactory::create_level_state() {
    LevelState* l = new LevelState{};
    return l;
}
PausedState* StateFactory::create_paused_state() {
    PausedState* p = new PausedState{};
    return p;
}
VictoryState* StateFactory::create_victory_state() {
    VictoryState* v = new VictoryState{};
    return v;
}